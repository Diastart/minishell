/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:17:33 by Dias              #+#    #+#             */
/*   Updated: 2025/05/09 15:57:42 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minihsell.h"

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("/nexit/n");
			break ;
		}
		if (*input)
			add_history(input);
		process(input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
