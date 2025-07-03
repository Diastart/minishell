/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:12:09 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:45:54 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	g_status;

char	*expand(t_env *env, char *envstr)
{
	if (envstr == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(env->key, envstr) == 0)
			return (ft_dupsubstr(env->val, env->val + ft_strlen(env->val)));
		env = env->next;
	}
	return (NULL);
}

char	*rmv_quotes_and_expand(t_env *env, char *rmtval)
{
	char	*result;
	char	*start;
	char	*substr;
	char	quote;

	result = NULL;
	start = rmtval;
	while (*(rmtval) != '\0')
	{
		if (*(rmtval) == '\'' || *(rmtval) == '\"')
		{
			quote = *(rmtval);
			result = ft_strjoin(result, ft_dupsubstr(start, rmtval));
			start = ++(rmtval);
			skip_untill_quote(&(rmtval), quote);
			substr = ft_dupsubstr(start, rmtval);
			if (quote == '\"')
				substr = search_and_expand(env, substr);
			result = ft_strjoin(result, substr);
			start = ++(rmtval);
		}
		else
			(rmtval)++;
	}
	result = ft_strjoin(result, ft_dupsubstr(start, rmtval));
	return (result);
}

char	*search_and_expand(t_env *env, char *rmtval)
{
	char	*result;
	char	*start;
	char	*envstr;

	result = NULL;
	if (rmtval == NULL)
		return (NULL);
	start = rmtval;
	while (*(rmtval) != '\0')
	{
		if (*(rmtval) == '$')
		{
			result = ft_strjoin(result, ft_dupsubstr(start, rmtval));
			start = ++(rmtval);
			if (*(rmtval) == '?')
			{
				result = ft_strjoin(result, ft_itoa(g_status));
				start = ++(rmtval);
				continue ;
			}
			skip_envchrs(&(rmtval));
			envstr = expand(env, ft_dupsubstr(start, rmtval));
			result = ft_strjoin(result, envstr);
			start = rmtval;
		}
		else 
			rmtval++;
	}
	result = ft_strjoin(result, ft_dupsubstr(start, rmtval));
	return (result);
}

void	expansion(t_mini *mini)
{
	t_token	*lcltoken;
	t_env	*lclenv;

	lcltoken = mini->token;
	lclenv = mini->env;
	while (lcltoken != NULL)
	{
		if (lcltoken->type == TOKEN_WORD)
			lcltoken->val = search_and_expand(lclenv, lcltoken->val);
		if (lcltoken->type == TOKEN_QUOTE)
		{
			lcltoken->val = rmv_quotes_and_expand(lclenv, lcltoken->val);
			lcltoken->type = TOKEN_WORD;
		}
		lcltoken = lcltoken->next;
	}
}
