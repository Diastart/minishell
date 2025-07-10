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
