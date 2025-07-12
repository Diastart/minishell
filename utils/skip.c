/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:58:48 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 19:29:57 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

static int	is_alphanum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

void	skip_envchrs(char **line)
{
	while ((**line) != '\0' && is_alphanum(**line))
		(*line)++;
}

void	skip_whitespaces(char **line)
{
	if (*line == NULL)
		return ;
	while (**line != '\0' && **line == ' ')
		(*line)++;
}

void	skip_until_quote(char **line, char quote)
{
	while (**line != '\0' && **line != quote)
		(*line)++;
}
