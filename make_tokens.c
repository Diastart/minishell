/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:03:00 by Dias              #+#    #+#             */
/*   Updated: 2025/07/01 12:14:27 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	slen(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

int	cmpr(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_token_type	get_token_type_extra(char *token_val)
{
	char	quote;

	quote = '\0';
	while (*token_val != '\0')
	{
		if (*token_val == '\'' || *token_val == '\"')
		{
			quote = *token_val++;
			while (*token_val != '\0' && *token_val != quote)
				token_val++;
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
	if (cmpr(token_val, "|") == 0)
		return (TOKEN_PIPE);
	else if (cmpr(token_val, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	else if (cmpr(token_val, "<<") == 0)
		return (TOKEN_REDIR_HEREDOC);
	else if (cmpr(token_val, ">") == 0)
		return (TOKEN_REDIR_OUT);
	else if (cmpr(token_val, "<") == 0)
		return (TOKEN_REDIR_IN);
	else
		return (get_token_type_extra(token_val));
}

char	*get_token_value(char **line)
{
	char	*head;
	char	*token_val;
	char	*start;
	char	quote;

	start = (*line);
	while ((**line) != '\0' && (**line) != ' ' && (**line) != '|'
	&& (**line) != '>' && (**line) != '<')
	{
		if ((**line) == '\'' || (**line) == '\"')
		{
			quote = *(*line)++;
			while ((**line) != '\0' && (**line) != quote)
				(*line)++;
			if (**line == '\0')
				break ;
		}
		(*line)++;
	}
	if (start == *line && (**line) == '>')
	{
		if (*(*line + 1) == '>')
			*line += 2;
		else
			*line += 1;
	}
	if (start == *line && (**line) == '<')
	{
		if (*(*line + 1) == '<')
			*line += 2;
		else
			*line += 1;
	}
	if (start == *line && (**line) == '|')
		*line += 1;
	token_val = malloc(sizeof(char) * ((*line) - start + 1));
	head = token_val;
	while (start < (*line))
		*token_val++ = *start++;
	*token_val = '\0';
	return (head);
}

t_token	*create_token(char **line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->val = get_token_value(line);
	token->type = get_token_type(token->val);
	token->next = NULL;
	return (token);
}

void	connect_token(t_mini *mini, t_token *token)
{
	t_token	*temp;

	if (mini->token == NULL)
	{
		mini->token = token;
		return ;
	}
	temp = mini->token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = token;
	return ;
}

void	make_tokens(t_mini *mini, char *line)
{
	while (*line != '\0')
	{
		while(*line != '\0' && *line == ' ')
			line++;
		if (*line == '\0')
			break ;
		connect_token(mini, create_token(&line));
	}
}
