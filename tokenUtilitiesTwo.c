/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenUtilitiesTwo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:49:12 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:02:10 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

void	shift_if_spr_were_first(char *start, char **line)
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
