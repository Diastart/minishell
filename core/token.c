/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:12:22 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 18:41:09 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_status;

static t_token_type	get_token_type(char *token_val)
{
	if (ft_strcmp(token_val, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(token_val, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	else if (ft_strcmp(token_val, "<<") == 0)
		return (TOKEN_REDIR_HEREDOC);
	else if (ft_strcmp(token_val, ">") == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strcmp(token_val, "<") == 0)
		return (TOKEN_REDIR_IN);
	else
		return (TOKEN_WORD);
}

static char	*get_token_val(char **line, t_token *lcltoken)
{
	char	*start;
	char	quote;

	start = (*line);
	while (!nspr(**line))
	{
		if ((**line) == '\'' || (**line) == '\"')
		{
			quote = *(*line)++;
			skip_until_quote(line, quote);
			if (**line == '\0')
			{
				g_status = 257;
				lcltoken->state = KO;
				return (NULL);
			}
		}
		(*line)++;
	}
	shift(start, line);
	return (ft_substrdup(start, *line));
}

static t_token	*create_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->val = NULL;
	new_token->type = TOKEN_UNSET;
	new_token->state = OK;
	new_token->next = NULL;
	return (new_token);
}

static int	make_token(t_mini *mini, char **line)
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
	tailtoken->val = get_token_val(line, tailtoken);
	if (tailtoken->state == KO)
		return (KO);
	tailtoken->type = get_token_type(tailtoken->val);
	if (tailtoken->type == TOKEN_WORD)
		update(tailtoken, mini);
	return (OK);
}

int	token_flow(t_mini *mini, char *line)
{
	if (line == NULL)
		return (KO);
	while (*line != '\0')
	{
		skip_whitespaces(&line);
		if (*line == '\0')
			return (OK);
		if (make_token(mini, &line) == KO)
			return (KO);
	}
	return (OK);
}
