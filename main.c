/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:32:41 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 23:12:18 by Dias             ###   ########.fr       */
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
		if(manifest_tokens(mini))
			continue ;
		printf("BEFORE EXPANSION\n");
		print_tokens(mini);
		printf("AFTER EXPANSION\n");
		expansion(mini);
		print_tokens(mini);
		set_cmds(mini);
		if (manifest_redirs(mini))
			continue ;
		print_commands(mini);
	}
	
}
