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

void	child(int pipefd[2], int carry, t_cmd *cmd, t_mini *mini)
{
	char	*cmd_path;

	set_signals();
	cmd_path = find_command_in_path(mini, cmd->args[0]);
	redirinout(cmd);
	if (!has_redir_in(cmd) && carry != TERMINAL)
		dup2(carry, STDIN_FILENO);
	if (cmd->next && !has_redir_out(cmd))
		dup2(pipefd[WRITE_KEY], STDOUT_FILENO);
	if (cmd->next && pipefd[READ_KEY] != -1)
		close(pipefd[READ_KEY]);
	if (cmd->next && pipefd[WRITE_KEY] != -1)
		close(pipefd[WRITE_KEY]);
	if (carry != TERMINAL && carry != -1)
		close(carry);
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (is_builtin(cmd))
		exit(trash(cmd, mini, cmd_path));
	validate_and_exec_cmd(mini, cmd, cmd_path);
}

void	parent(int pipefd[2], int *carry, t_cmd *cmd)
{
	if (cmd->next)
		close(pipefd[WRITE_KEY]);
	if (*carry != TERMINAL)
		close(*carry);
	if (cmd->next)
		*carry = pipefd[READ_KEY];
	else
		*carry = TERMINAL;
}

void	wait_children(t_mini *mini, pid_t last_pid, int carry)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(status))
				mini->exit_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				mini->exit_status = WEXITSTATUS(status);
		}
		wpid = waitpid(-1, &status, 0);
	}
	if (carry != TERMINAL)
		close(carry);
}

int	routing_flow(t_mini *mini)
{
	t_cmd	*lclcmd;
	pid_t	last_pid;
	int		carry;

	last_pid = -1;
	carry = TERMINAL;
	lclcmd = mini->cmd;
	if (is_builtin(lclcmd) && lclcmd->next == NULL)
		return (mini->exit_status = exec_single_builtin(mini, lclcmd));
	while (lclcmd != NULL)
	{
		if (!lclcmd->args || !lclcmd->args[0])
		{
			mini->exit_status = 0;
			lclcmd = lclcmd->next;
			continue ;
		}
		if (exec_command(mini, lclcmd, &carry, &last_pid) != 0)
			return (1);
		lclcmd = lclcmd->next;
	}
	wait_children(mini, last_pid, carry);
	return (mini->exit_status);
}
