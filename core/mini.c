/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:09:58 by dias              #+#    #+#             */
/*   Updated: 2025/07/20 12:19:55 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

volatile sig_atomic_t	g_status;

static int	get_glblenvlen(char **glblenv)
{
	int	len;

	len = 0;
	if (glblenv == NULL)
		return (0);
	while (glblenv[len])
		len++;
	return (len);
}

void	copy(t_mini *mini, char **glblenv)
{
	int		i;
	int		len;
	char	**result;

	len = get_glblenvlen(glblenv);
	result = malloc(sizeof(char *) * (len + 1));
	if (result == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(glblenv[i]);
		i++;
	}
	result[i] = NULL;
	mini->env = result;
}

static t_mini	*create(void)
{
	t_mini	*new_mini;

	new_mini = malloc(sizeof(t_mini));
	if (new_mini == NULL)
		return (NULL);
	new_mini->env = NULL;
	new_mini->token = NULL;
	new_mini->cmd = NULL;
	new_mini->exit_status = 0;
	return (new_mini);
}

int	main(int ac, char **av, char **glblenv)
{
	t_mini				*mini;

	(void)ac;
	(void)av;
	set_signals();
	mini = create();
	copy(mini, glblenv);
	while (42)
	{
		if (under_flow(mini) == OK)
			routing_flow(mini);
		free_flow(mini, NOENV);
	}
	free_flow(mini, ENV);
	free(mini);
	return (mini->exit_status);
}
