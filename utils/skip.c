/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:58:48 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 16:41:34 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

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
