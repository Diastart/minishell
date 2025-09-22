/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:43:32 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:43:38 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	builtin_env(t_mini *mini, t_cmd *cmd)
{
	char	**args;
	char	**env;
	int		i;

	args = cmd->args;
	env = mini->env;
	i = 0;
	if (args[1])
	{
		printf("env: \'%s\': No such file or directory\n", args[1]);
		return (1);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
