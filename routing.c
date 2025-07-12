/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:02:39 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 20:15:08 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_last	redirinout(t_cmd *lclcmd, t_last *lastredirs)
{
	int		fd;
	t_redir	*lclredir;

	lastredirs->delim = NULL;
	lastredirs->newline = OK;
	lclredir = lclcmd->redir;
	while (lclredir != NULL)
	{
		if (lclredir->filename != NULL)
			lclredir->filename = lclredir->filename;
		if (lclredir->type == REDIR_IN)
		{
			lastredirs->delim = NULL;
			fd = open(lclredir->filename, O_RDONLY, 0777);
			if (fd == -1)
				exit(259);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_HEREDOC)
		{
			lastredirs->delim = lclredir->filename;
			fd = open(lclredir->filename, O_WRONLY | O_CREAT, 0777);
			if (fd == -1)
				exit(259);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_OUT)
		{
			lastredirs->newline = OK;
			fd = open(lclredir->filename, O_WRONLY | O_CREAT, 0777);
			if (fd == -1)
				exit(259);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_APPEND)
		{
			lastredirs->newline = KO;
			fd = open(lclredir->filename, O_RDONLY, 0777);
			if (fd == -1)
				exit(259);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		lclredir = lclredir->next;
	}
}


static void	child(int pipefd[], int carry, t_cmd *lclcmd)
{
	t_last	lastredirs;
	
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
	redirinout(lclcmd, &lastredirs);
	execute_flow(lclcmd, &lastredirs);
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