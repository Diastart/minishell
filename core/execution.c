/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:13:23 by dias              #+#    #+#             */
/*   Updated: 2025/07/20 12:41:39 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	trash(t_cmd *cmd, t_mini *mini, char *cmd_path)
{
	int	stat;

	if (cmd_path)
		free(cmd_path);
	stat = exec_builtin(cmd, mini);
	free_flow(mini, ENV);
	free(mini);
	return (stat);
}

int	exec_builtin(t_cmd *cmd, t_mini *mini)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(mini));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(mini));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(mini));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(mini, cmd));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(mini));
	else
		return (1);
}

int	is_builtin(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->args[0];
	if (!ft_strcmp(arg, "echo"))
		return (1);
	if (!ft_strcmp(arg, "cd"))
		return (1);
	if (!ft_strcmp(arg, "pwd"))
		return (1);
	if (!ft_strcmp(arg, "export"))
		return (1);
	if (!ft_strcmp(arg, "unset"))
		return (1);
	if (!ft_strcmp(arg, "env"))
		return (1);
	if (!ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}
