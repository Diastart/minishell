/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:09:58 by dias              #+#    #+#             */
/*   Updated: 2025/07/11 17:57:50 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_status;

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

static void	copy(t_mini *mini, char **glblenv)
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
	return (new_mini);
}

static int	under_flow(t_mini *mini)
{
	int		lclstate;
	char	*line;

	lclstate = OK;
	line = readline("> ");
	if (pipe_first(line) == KO)
		return (KO);
	if (token_flow(mini, line) == KO)
		return (KO);
	if (consec_pipes(mini) == KO)
		return (KO);
	if (pipe_last(mini) == OK)
	{
		lclstate = under_flow(mini);
		return (lclstate);
	}
	print_tokens(mini);
	if (command_flow(mini) == KO)
		return (KO);
	print_cmds(mini);
	return (lclstate);
}

int	main(int ac, char **av, char **glblenv)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	mini = create();
	copy(mini, glblenv);
	while (42)
	{
		ft_putstr("$dias_eugenio_shell");
		if (under_flow(mini) == OK)
			g_status = 0;
			//routing_flow(mini);
		free_flow(mini, NOENV);
	}
}
