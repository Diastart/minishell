/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:44:21 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:44:33 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

void	export_env_print(char **new_env)
{
	char	*delim;
	int		i;

	i = 0;
	while (new_env[i])
	{
		delim = ft_strchr(new_env[i], '=');
		write(1, "declare -x ", 11);
		if (delim)
		{
			write(1, new_env[i], delim - new_env[i]);
			write(1, "=\"", 2);
			write(1, delim + 1, ft_strlen(delim + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, new_env[i], ft_strlen(new_env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	export_env(t_mini *mini, char *str)
{
	char	**new_env;
	char	**env;
	int		i;

	i = 0;
	env = mini->env;
	new_env = malloc ((ft_matrixlen(env) + 1 + 1) * sizeof(char *));
	if (!new_env)
		return ;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free_env(env);
	mini->env = new_env;
}

void	new_vars(t_mini *mini, char *str)
{
	int		i;
	int		len;
	char	*value;

	i = -1;
	len = var_name_len(str);
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], str, len - 1) == 0
			&& str[len - 1] == '+' && str[len] == '=')
		{
			value = ft_substrdup(ft_strchr(str, '=') + 1, ft_strchr(str, '\0'));
			mini->env[i] = ft_strjoin_tmp(mini->env[i], value, 1);
			return ;
		}
		else if (ft_strncmp(mini->env[i], str, len - 1) == 0
			&& (str[len] == '=' || str[len] == '\0'))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(str);
			return ;
		}
	}
	export_env(mini, str);
}

int	builtin_export(t_mini *mini)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!mini->cmd->args[1])
	{
		sort_matrix(mini->env);
		export_env_print(mini->env);
		return (0);
	}
	while (mini->cmd->args[++i])
	{
		if (is_valid_varname(mini->cmd->args[i]))
		{
			tmp = unquote(mini, mini->cmd->args[i]);
			new_vars(mini, tmp);
			free(tmp);
		}
		else
		{
			print_stderr_export(mini->cmd->args[i]);
			mini->exit_status = 1;
		}
	}
	return (mini->exit_status);
}
