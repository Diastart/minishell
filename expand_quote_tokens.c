/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:42:40 by Dias              #+#    #+#             */
/*   Updated: 2025/07/01 13:19:03 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

char	*subdup(char *s1, char *s2)
{
	char	*s3;
	char	*s3_h;

	if (s1 >= s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (s2 - s1 + 1));
	s3_h = s3;
	while (s1 < s2)
	{
		*s3 = *s1;
		s1++;
		s3++;
	}
	*s3 = '\0';
	return (s3_h);
}

int	is_alphanum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
	|| c == '_')
		return (1);
	return (0);
}

char	*env_exp(t_mini *mini, char *s)
{
	t_env	*current;

	if (s == NULL)
		return (NULL);
	current = mini->env;
	while (current != NULL)
	{
		if (cmpr(current->key, s) == 0)
			return (subdup(current->val, current->val + slen(current->val)));
		current = current->next;
	}
	return (NULL);
}

char	*merge(char *s1, char *s2)
{
	char	*s3;
	char	*s3_h;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s3 = malloc(sizeof(char) * (slen(s1) + slen(s2) + 1));
	s3_h = s3;
	if (s1 != NULL)
	{
		while (*s1 != '\0')
			*s3++ = *s1++;
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
			*s3++ = *s2++;
	}
	*s3 = '\0';
	return (s3_h);
}

// do not forget to implement $? case
char	*dquote(t_mini *mini, char *s)
{
	char	*res;
	char	*s1;
	char	*s2;
	char	*env;

	res = NULL;
	if (s == NULL)
		return (NULL);
	s1 = s;
	s2 = s1;
	while (*s2 != '\0')
	{
		if (*s2 == '$')
		{
			res = merge(res, subdup(s1, s2));
			s2++;
			s1 = s2;
			while (*s2 != '\0' && is_alphanum(*s2))
				s2++;
			env = env_exp(mini, subdup(s1, s2));
			res = merge(res, env);
			s1 = s2;
		}
		else
			s2++;
	}
	res = merge(res, subdup(s1, s2));
	return (res);
}

void	update(t_mini *mini, t_token *current)
{
	char	*s1;
	char	*s2;
	char	*s;
	char	*res;
	char	quote;

	res = NULL;
	s1 = current->val;
	s2 = s1;
	while (*s2 != '\0')
	{
		if (*s2 == '\'' || *s2 == '\"')
		{
			quote = *s2;
			res = merge(res, subdup(s1, s2));
			s2++;
			s1 = s2;
			while (*s2 != quote)
				s2++;
			s = subdup(s1, s2);
			if (quote == '\"')
				s = dquote(mini, s);
			res = merge(res, s);
			s2++;
			s1 = s2;
		}
		else
			s2++;
	}
	res = merge(res, subdup(s1, s2));
	free(current->val);
	current->val = res;
}

void	quote_exp(t_mini *mini)
{
	t_token	*current;

	current = mini->token;
	while (current != NULL)
	{
		if (current->type == TOKEN_QUOTE)
		{
			update(mini, current);
			current->type = TOKEN_WORD;
		}
		current = current->next;
	}
}
