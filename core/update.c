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

static char	*expand(t_mini *mini, char *envstr)
{
	char	*copy;
	char	**env;

	env = mini->env;
	if (envstr == NULL)
	{
		free(envstr);
		return (NULL);
	}
	while (*env != NULL)
	{
		if (ft_strncmp(*env, envstr, ft_strlen(envstr)) == 0
			&& (*env)[ft_strlen(envstr)] == '=')
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

static char	*dollar(t_mini *mini, char **val, char **start, char *res)
{
	res = ft_strjoin_tmp(res, ft_substrdup(*start, *val), 1);
	*start = ++(*val);
	if (**val == '?')
	{
		res = ft_strjoin_tmp(res, ft_itoa(mini->exit_status), 1);
		*start = ++(*val);
		return (res);
	}
	if (**val == '\0' || **val == ' ' || **val == '"' || **val == '\''
		|| (!ft_isalpha(**val) && **val != '_'))
	{
		return (ft_strjoin_tmp(res, ft_strdup("$"), 1));
	}
	skip_envchrs(val);
	res = ft_strjoin_tmp(res, expand(mini, ft_substrdup(*start, *val)), 1);
	*start = *val;
	return (res);
}

char	*search(t_mini *mini, char *val)
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
			res = dollar(mini, &val, &start, res);
		else
			val++;
	}
	return (ft_strjoin_tmp(res, ft_substrdup(start, val), 1));
}

char	*unquote(t_mini *mini, char *val)
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
			res = join_search(mini, res, start, val);
			start = ++val;
			skip_until_quote(&val, quote);
			if (quote == '\"')
				res = join_search(mini, res, start, val);
			else
				res = ft_strjoin_tmp(res, ft_substrdup(start, val), 1);
			start = ++val;
		}
		else
			val++;
	}
	return (res = ft_strjoin_tmp(res,
			search_free(mini, ft_substrdup(start, val)), 1));
}

void	update(t_token *lcltoken, t_mini *mini)
{
	char	*res;

	res = unquote(mini, lcltoken->val);
	free(lcltoken->val);
	lcltoken->val = res;
}
