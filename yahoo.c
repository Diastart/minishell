/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yahoo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:25:07 by Dias              #+#    #+#             */
/*   Updated: 2025/07/07 17:26:16 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"
#define TERMINAL -1

int	g_status;

void	reset_pipe(int *prev_pipe_stdin, t_cmd *lclcmd, int *next_pipe_stds)
{
	close(next_pipe_stds[1]);
	if (*prev_pipe_stdin != TERMINAL)
		close(*prev_pipe_stdin);
	if (lclcmd->next != NULL)
		*prev_pipe_stdin = next_pipe_stds[0]; // VERY IMORTANT
	else
		*prev_pipe_stdin = TERMINAL;
}

void	set_redirs(t_cmd *lclcmd)
{
	t_redir	*lclredir;

	lclredir = lclcmd->redir;
	while (lclredir != NULL)
	{
		if (lclredir->type == REDIR_INPUT)
		{
			int fd = open(lclredir->filename, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (lclredir->type == REDIR_OUTPUT)
		{
			int fd = open(lclredir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		lclredir = lclredir->next;
	}
}

void	set_std_out(int *next_pipe_stds, t_cmd *lclcmd)
{
	if(lclcmd->next != NULL)
	{
		dup2(next_pipe_stds[1], STDOUT_FILENO);
		close(next_pipe_stds[0]);
		close(next_pipe_stds[1]);
	}
}

void	set_std_in(int prev_pipe_stdin)
{
	if (prev_pipe_stdin != TERMINAL)
	{
		dup2(prev_pipe_stdin, STDIN_FILENO);
		close(prev_pipe_stdin);
	}
}

void	create_pipe(int *next_pipe_stds[], t_cmd *lclcmd)
{
	if (lclcmd->next != NULL)
		pipe(*next_pipe_stds);
}

void	yahoo(t_mini *mini)
{
	int		next_pipe_stds[2];
	int		prev_pipe_stdin;
	t_cmd	*lclcmd;
	pid_t	child_pid;

	prev_pipe_stdin = TERMINAL;
	lclcmd = mini->cmd;
	while (lclcmd != NULL)
	{
		create_pipe(&next_pipe_stds, lclcmd);
		child_pid = fork();
		if (child_pid == 0)
		{
			set_std_in(prev_pipe_stdin);
			set_std_out(next_pipe_stds, lclcmd);
			set_redirs(lclcmd);
			/*
			exec_cmd();
			if (g_status != 0)
				break ;
			*/
			exit(0);
		}
		else
			reset_pipe(&prev_pipe_stdin, lclcmd, next_pipe_stds);
		lclcmd = lclcmd->next;
	}
}