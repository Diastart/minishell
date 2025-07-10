/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:02:56 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 15:03:06 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	ft_listlen(char **listofstr)
{
	int	len;

	len = 0;
	while (listofstr != NULL && *listofstr != NULL)
	{
		len++;
		listofstr++;
	}
	return (len);
}
