/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:50:09 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:50:54 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 0;
	while (str[i])
	{
		j = 0;
		flag = 0;
		while (accept[j])
		{
			if (str[i] == accept[j])
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (!flag)
			break ;
		i++;
	}
	return (i);
}
