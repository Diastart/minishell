/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:42:25 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 16:44:44 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	under_flow(t_mini *mini)
{
	int		lclstate;
	char	*line;

	lclstate = OK;
	line = readline(BASH);
	if (!line)
	{
		free_flow(mini, ENV);
		free(mini);
		print_stdout("exit");
		exit(0);
	}
	if (*line != '\0')
		add_history(line);
	if (pipe_first(line) == KO || token_flow(mini, line) == KO
		|| consec_pipes(mini) == KO)
		lclstate = KO;
	if (pipe_last(mini) == OK)
		return (free(line), under_flow(mini));
	if (command_flow(mini) == KO)
		lclstate = KO;
	return (free(line), lclstate);
}
