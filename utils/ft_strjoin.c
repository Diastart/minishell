/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:15:54 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 20:40:34 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str;
	int		i;
	int		j;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (str1 != NULL)
	{
		while (str1[j] != '\0')
			str[i++] = str1[i++];
	}
	j = 0;
	if (str2 != NULL)
	{
		while (str2[j] != '\0')
			str[i++] = str2[j++];
	}
	str[i] = '\0';
	free(str1);
	free(str2);
	return (str);
}
