/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:53:29 by dias              #+#    #+#             */
/*   Updated: 2025/07/01 12:13:04 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

char	*get_left_env(char *env_line)
{
	int		delim;

	delim = 0;
	while (env_line[delim] != '=')
		delim++;
	return (subdup(env_line, env_line + delim));
}

char	*get_right_env(char *env_line)
{
	int		delim;

	delim = 0;
	while (env_line[delim] != '=')
		delim++;
	return (subdup(env_line + delim + 1, env_line + slen(env_line)));
}

t_env	*create_env(char *env_line)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = get_left_env(env_line);
	env->val = get_right_env(env_line);
	env->next = NULL;
	return (env);
}

void	connect_env(t_mini *mini, t_env *env)
{
	t_env	*temp;

	if (mini->env == NULL)
	{
		mini->env = env;
		return ;
	}
	temp = mini->env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = env;
	return ;
}

void	copy_envps(t_mini *mini, char **envp)
{
	while(*envp)
		connect_env(mini,create_env(*envp++));
}
