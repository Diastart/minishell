/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalUtilitiesTwo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:38:54 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 14:52:54 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	ft_intlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

int	is_alphanum(char c)
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

void	skip_envchrs(char **ptr)
{
	while ((**ptr) != '\0' && is_alphanum(**ptr))
		(*ptr)++;
}
