/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:32:41 by Dias              #+#    #+#             */
/*   Updated: 2025/07/07 17:28:21 by dias             ###   ########.fr       */
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
			yahoo(mini);
		//print_error();
	}
}
