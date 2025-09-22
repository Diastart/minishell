/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:45:53 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 16:42:58 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	nspr(char c)
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

void	shift(char *start, char **line)
{
	if (start == *line && (**line) == '>')
	{
		if (*(*line + 1) == '>')
			*line += 2;
		else
			*line += 1;
	}
	else if (start == *line && (**line) == '<')
	{
		if (*(*line + 1) == '<')
			*line += 2;
		else
			*line += 1;
	}
	else if (start == *line && (**line) == '|')
		*line += 1;
}

char	*ft_strjoin_tmp(char *res, char *tmp, int free_res)
{
	char	*new;

	new = ft_strjoin(res, tmp);
	if (tmp)
		free(tmp);
	if (free_res && res)
		free(res);
	return (new);
}

char	*search_free(t_mini *mini, char *tmp)
{
	char	*res;

	res = search(mini, tmp);
	free(tmp);
	return (res);
}

char	*join_search(t_mini *mini, char *res, char *start, char *end)
{
	return (ft_strjoin_tmp(res,
			search_free(mini, ft_substrdup(start, end)), 1));
}
