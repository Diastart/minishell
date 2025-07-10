/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:02:39 by dias              #+#    #+#             */
/*   Updated: 2025/07/11 00:12:47 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
static void	redir(t_cmd *lclcmd)
{
	SET ROUTING DEPENDING ON INTERNAL REDIRECTIONS OF A COMMAND
}
*/

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
	//redir(lclcmd);
	//execute_flow(lclcmd);
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