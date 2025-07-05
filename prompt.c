/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:46:22 by Dias              #+#    #+#             */
/*   Updated: 2025/07/05 18:36:59 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	get_cmds(t_mini *mini)
{
	char	*line;
	int		error;

	error = 0;
	line = readline("> ");
	tokenize(mini, line);
	if (manifest(mini, PIPELAST))
	{
		error = get_cmds(mini);
		return (error);
	}
	//print_tokens(mini);
	if (manifest(mini, PIPEFIRST) || manifest(mini, ERRTOKENS))
		return (1);
	expansion(mini);
	//print_tokens(mini);
	set_cmds(mini);
	if (manifest(mini, REDIRS))
		return (1);
	return (error);
}
