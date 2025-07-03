/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenUtilitiesOne.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:49:28 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 13:48:01 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->val = NULL;
	token->type = TOKEN_UNSET;
	token->next = NULL;
	return (token);
}

t_token	*setget_tailtoken(t_mini *mini)
{
	t_token	*lcltoken;
	t_token	*tailtoken;

	tailtoken = create_token();
	lcltoken = mini->token;
	if (lcltoken == NULL)
		mini->token = tailtoken;
	else
	{
		while (lcltoken->next != NULL)
			lcltoken = lcltoken->next;
		lcltoken->next = tailtoken;
	}
	return (tailtoken);
}

void	skip_whitespaces(char **line)
{
	while (**line != '\0' && **line == ' ')
		(*line)++;
}

void	skip_untill_quote(char **line, char quote)
{
	while (**line != '\0' && (**line) != quote)
		(*line)++;
}

int	is_nspr(char c)
{
	if (c == '\0')
		return (1);
	else if (c == ' ')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	return (0);
}
