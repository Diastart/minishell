/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:50:08 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 20:28:03 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_status;

static char	*expand(char **env, char *envstr)
{
	char	*copy;

	if (envstr == NULL)
	{
		free(envstr);
		return (NULL);
	}
	while (*env != NULL)
	{
		if (ft_strcmp(*env, envstr) == 61)
		{
			copy = *env;
			skip_until_quote(&copy, '=');
			free(envstr);
			return (ft_strdup(++copy));
		}
		env++;
	}
	free(envstr);
	return (NULL);
}

static char	*dollar(char **env, char **val, char **start, char *res)
{
	res = ft_strjoin(res, ft_substrdup(*start, *val));
	*start = ++(*val);
	if (**val == '?')
	{
		res = ft_strjoin(res, ft_itoa(g_status));
		*start = ++(*val);
		return (res);
	}
	skip_envchrs(val);
	res = ft_strjoin(res, expand(env, ft_substrdup(*start, *val)));
	*start = *val;
	return (res);
}

static char	*search(char **env, char *val)
{
	char	*res;
	char	*start;

	res = NULL;
	if (val == NULL)
		return (NULL);
	start = val;
	while (*val != '\0')
	{
		if (*val == '$')
			res = dollar(env, &val, &start, res);
		else
			val++;
	}
	return (ft_strjoin(res, ft_substrdup(start, val)));
}

static char	*unquote(char **env, char *val)
{
	char	*res;
	char	*start;
	char	quote;

	start = val;
	res = NULL;
	while (*val != '\0')
	{
		if (*val == '\'' || *val == '\"')
		{
			quote = *val;
			res = ft_strjoin(res, search(env, ft_substrdup(start, val)));
			start = ++val;
			skip_until_quote(&val, quote);
			if (quote == '\"')
				res = ft_strjoin(res, search(env, ft_substrdup(start, val)));
			else
				res = ft_strjoin(res, ft_substrdup(start, val));
			start = ++val;
		}
		else
			val++;
	}
	res = ft_strjoin(res, search(env, ft_substrdup(start, val)));
	return (res);
}

void	update(t_token *lcltoken, t_mini *mini)
{
	char	*res;

	res = unquote(mini->env, lcltoken->val);
	free(lcltoken->val);
	lcltoken->val = res;
}
