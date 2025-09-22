/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:43:57 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:44:02 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	builtin_exit(t_mini *mini)
{
	char	**args;
	int		exit_status;

	args = mini->cmd->args;
	exit_status = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			print_stderr_exit(args[1]);
			exit(2);
		}
		exit_status = ft_atoi(args[1]);
		if (args[2])
		{
			print_stderr_args(args[2]);
			return (1);
		}
	}
	free_flow(mini, ENV);
	free(mini);
	exit(exit_status & 0xFF);
}
