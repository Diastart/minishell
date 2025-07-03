/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:05:24 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:44:10 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

t_token_type	get_token_type_extra(char *token_val)
{
	char	quote;

	quote = '\0';
	while (*token_val != '\0')
	{
		if (*token_val == '\'' || *token_val == '\"')
		{
			quote = *token_val++;
			skip_untill_quote(&token_val, quote);
			if (*token_val == '\0')
				return (TOKEN_ERROR);
		}
		token_val++;
	}
	if (quote == '\0')
		return (TOKEN_WORD);
	return (TOKEN_QUOTE);
}

t_token_type	get_token_type(char *token_val)
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
		return (get_token_type_extra(token_val));
}

char	*get_token_val(char **line)
{
	char	*start;
	char	quote;

	start = (*line);
	while (!is_nspr(**line))
	{
		if ((**line) == '\'' || (**line) == '\"')
		{
			quote = *(*line)++;
			skip_untill_quote(line, quote);
		}
		(*line)++;
	}
	shift_if_spr_were_first(start, line);
	return (ft_dupsubstr(start, *line));
}

void	pack_token(t_token *token, char **line)
{
	token->val = get_token_val(line);
	token->type = get_token_type(token->val);
}

void	tokenize(t_mini *mini, char *line)
{
	t_token	*lcltoken;

	while (*line != '\0')
	{
		skip_whitespaces(&line);
		if (*line == '\0')
			break ;
		lcltoken = setget_tailtoken(mini);
		pack_token(lcltoken, &line);
	}
}
