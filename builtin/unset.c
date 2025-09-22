/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:45:14 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:45:19 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

void	remove_env_var(char **env, char *str)
{
	int	i;
	int	len;
	int	j;

	if (!env || !str || str[0] == '\0')
		return ;
	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len) && env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
			continue ;
		}
		i++;
	}
}

int	builtin_unset(t_mini *mini)
{
	char	**args;
	int		i;

	args = mini->cmd->args;
	i = 1;
	while (args[i])
	{
		remove_env_var(mini->env, args[i]);
		i++;
	}
	return (0);
}
