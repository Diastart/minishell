/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:32:19 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 16:42:02 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

char	*ft_substrdup(char	*str_ptr, char	*str_end)
{
	char	*substr;
	char	*head_substr;

	if (str_ptr >= str_end)
		return (NULL);
	substr = malloc(sizeof(char) * (str_end - str_ptr + 1));
	if (substr == NULL)
		return (NULL);
	head_substr = substr;
	while (str_ptr < str_end)
	{
		*substr = *str_ptr;
		substr++;
		str_ptr++;
	}
	*substr = '\0';
	return (head_substr);
}
