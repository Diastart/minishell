/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:32:41 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:23:33 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	char	*line;

	(void)ac;
	(void)av;

	mini = create_mini();
	copy_envps(mini, envp);
	//print_envps(mini);
	while (42)
	{
		reset_mini(mini);
		line = readline("$minishell> ");
		tokenize(mini, line);
		// manifest_tokens();
		printf("BEFORE EXPANSION\n");
		print_tokens(mini);
		printf("AFTER EXPANSION\n");
		expansion(mini);
		print_tokens(mini);
		// manifest_redirs();
		set_cmds(mini);
		print_commands(mini);
	}
	
}
