/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:03:00 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/18 22:03:05 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	validate_and_exec_cmd(t_mini *mini, t_cmd *cmd, char *cmd_path)
{
	struct stat	st;

	if (!cmd_path)
		print_stderr_cmd(cmd->args[0], mini);
	else if (stat(cmd_path, &st) != 0)
		print_stderr_file(cmd_path, mini);
	else if (S_ISDIR(st.st_mode))
		print_stderr_dir(cmd_path, mini);
	else if (access(cmd_path, X_OK) != 0)
		print_stderr_permission(cmd_path, mini);
	else if (execve(cmd_path, cmd->args, mini->env) == -1)
		print_stderr_cmd(cmd_path, mini);
	if (cmd_path)
		free(cmd_path);
	free_flow(mini, ENV);
	free(mini);
	exit(mini->exit_status);
}

int	has_redir_out(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	has_redir_in(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	exec_single_builtin(t_mini *mini, t_cmd *cmd)
{
	int	in;
	int	out;
	int	status;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (in == -1 || out == -1)
		return (perror("dup"), 1);
	redirinout(cmd);
	status = exec_builtin(cmd, mini);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (status);
}

int	exec_command(t_mini *mini, t_cmd *cmd, int *carry, pid_t *last_pid)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		child(pipefd, *carry, cmd, mini);
	else
	{
		parent(pipefd, carry, cmd);
		*last_pid = pid;
	}
	return (0);
}
