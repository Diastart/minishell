/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   under_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:41:36 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 17:13:41 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	g_status;

int	pipe_first(char *line)
{
	skip_whitespaces(&line);
	if (*line != '\0' && *line == '|')
	{
		g_status = 256;
		return (KO);
	}
	return (OK);
}

int	consec_pipes(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		if (lcltoken->type == TOKEN_PIPE && lcltoken->next != NULL \
			&& lcltoken->next->type == TOKEN_PIPE)
		{
			g_status = 256;
			return (KO);
		}
		lcltoken = lcltoken->next;
	}
	return (OK);
}

int	pipe_last(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	if (lcltoken != NULL)
	{
		while (lcltoken->next != NULL)
			lcltoken = lcltoken->next;
		if (lcltoken->type == TOKEN_PIPE)
			return (OK);
	}
	return (KO);
}
