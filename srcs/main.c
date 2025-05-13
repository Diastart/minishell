/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:15:50 by Dias              #+#    #+#             */
/*   Updated: 2025/05/13 17:18:01 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*cmdline;

	while (1)
	{
		cmdline = readline("minishell> ");
		printf("%s\n", cmdline);
		free(cmdline);
	}
}
