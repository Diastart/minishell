/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:02:39 by dias              #+#    #+#             */
/*   Updated: 2025/07/20 12:37:29 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


static int handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return -1;
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = readline("");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				if (line) free(line);
				break;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
		return pipefd[0];
	}
}

static int	redirinout(t_cmd *lclcmd)
{
	int		fd;
	int		nl;
	t_redir	*lclredir;

	nl = OK;
	lclredir = lclcmd->redir;
	while (lclredir != NULL)
	{
		if (lclredir->type == REDIR_IN)
		{
			fd = open(lclredir->filename, O_RDONLY, 0777);
			if (fd == -1)
				exit(259);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_HEREDOC)
		{
			fd = handle_heredoc(lclredir->filename);
			if (fd == -1)
				exit(259);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_OUT)
		{
			nl = OK;
			fd = open(lclredir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit(259);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_APPEND)
		{
			nl = KO;
			fd = open(lclredir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				exit(259);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		lclredir = lclredir->next;
	}
	return (nl);
}

static void	child(int pipefd[], int carry, t_cmd *lclcmd)
{
	if (carry != TERMINAL)
	{
		dup2(carry, STDIN_FILENO);
		close(carry);
	}
	if (lclcmd->next != NULL)
	{
		close(pipefd[READ_KEY]);
		dup2(pipefd[WRITE_KEY], STDOUT_FILENO);
		close(pipefd[WRITE_KEY]);
	}
	execute_flow(lclcmd, redirinout(lclcmd));
}

static void	parent(int pipefd[], int *carry, t_cmd *lclcmd)
{
	if (lclcmd->next != NULL)
		close(pipefd[WRITE_KEY]);
	if (*carry != TERMINAL)
		close(*carry);
	if (lclcmd->next != NULL)
		*carry = pipefd[READ_KEY];
	else
		*carry = TERMINAL;
	wait(NULL);
}

void	routing_flow(t_mini *mini)
{
	t_cmd	*lclcmd;
	pid_t	pid;
	int		pipefd[2];
	int		carry;

	carry = TERMINAL;
	lclcmd = mini->cmd;
	while (lclcmd != NULL)
	{
		if (lclcmd->next != NULL)
			pipe(pipefd);
		if (fork() == 0)
			child(pipefd, carry, lclcmd);
		parent(pipefd, &carry, lclcmd);
		lclcmd = lclcmd->next;
	}
}
