/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:32:41 by Dias              #+#    #+#             */
/*   Updated: 2025/07/05 18:32:50 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	g_status;

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	int		cmderror;

	(void)ac;
	(void)av;

	mini = create_mini();
	copy_envps(mini, envp);
	//print_envps(mini);
	while (42)
	{
		reset_mini(mini);
		printf("$minishell");
		cmderror = get_cmds((mini));
		if (!cmderror)
			print_cmds(mini);
	}
}
