/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:11:04 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 20:33:20 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

static int	ft_intlen(int n)
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

char	*ft_itoa(int status)
{
	char	*result;
	char	*head;
	int		len;

	len = ft_intlen(status);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	head = result;
	result += len;
	*result = '\0';
	while (--result >= head)
	{
		*result = (status % 10) + '0';
		status /= 10;
	}
	return (head);
}