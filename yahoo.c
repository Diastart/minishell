/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yahoo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:39:01 by Dias              #+#    #+#             */
/*   Updated: 2025/07/08 13:16:33 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

void	yahoo(t_mini *mini)
{
	t_cmd	*lclcmd;
	pid_t	pid;
	int		pipe[2];
	int		prev;

	prev = -1;
	lclcmd = mini->cmd;
	while (lclcmd != NULL)
	{
		if (lclcmd->next != NULL)
			pipe(pipe);
		pid = fork();
		if (pid == 0)
		{
			// CHILD
			if (prev != -1)
			{
				dup2(prev, STDIN_FILENO);
				close(prev);
			}
			if (lclcmd->next != NULL)
			{
				close(pipe[0]);
				dup2(pipe[1], STDOUT_FILENO);
				close(pipe[1]);
			}
			//set_redirs();
			//execute_cmd();
		}
		// PARENT
		close(prev);
		close(pipe[1]);
		if (lclcmd->next != NULL)
			prev = pipe[0];
		else
			prev = -1;
	}
}
