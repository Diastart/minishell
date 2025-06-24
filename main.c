/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:54:00 by Dias              #+#    #+#             */
/*   Updated: 2025/06/24 15:04:22 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

char	*get_left_env(char *env_line)
{
	char	*head;
	char	*left_side;
	int		len;

	len = 0;
	while (env_line[len] != '=')
		len++;
	left_side = malloc(sizeof(char) * (len + 2));
	head = left_side;
	while (*env_line != '=')
		*left_side++ = *env_line++;
	*left_side++ = '=';
	*left_side = '\0';
	return (head);
}

char	*get_right_env(char *env_line)
{
	char	*head;
	char	*right_side;
	int		len;
	int		delim;

	len = 0;
	while (env_line[len] != '\0')
	{
		if (env_line[len] == '=')
			delim = len;
		len++;
	}
	right_side = malloc(sizeof(char) * (len - delim));
	head = right_side;
	env_line += delim + 1;
	while (*env_line != '\0')
		*right_side++ = *env_line++;
	*right_side = '\0';
	return (head);
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

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	copy_envps(mini, envp);
	
	// NOW we have (key,value) -> (key,value)->...->NULL
	// linked list of environment variables
	while (mini->env !=  NULL)
	{
		printf("%s%s\n", mini->env->key, mini->env->val);
		mini->env = mini->env->next;
	}
	

}
