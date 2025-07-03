/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalUtilitiesOne.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:46:08 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:04:20 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_dupsubstr(char	*str_ptr, char	*str_end)
{
	char	*substr;
	char	*head_substr;

	if (str_ptr >= str_end)
		return (NULL);
	substr = malloc(sizeof(char) * (str_end - str_ptr + 1));
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

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str;
	char	*head;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	head = str;
	if (str1 != NULL)
	{
		while (*str1 != '\0')
			*str++ = *str1++;
	}
	if (str2 != NULL)
	{
		while (*str2 != '\0')
			*str++ = *str2++;
	}
	*str = '\0';
	//free(str1);
	//free(str2);
	return (head);
}

char	*ft_itoa(int status)
{
	char	*result;
	char	*head;
	int		len;

	len = ft_intlen(status);
	result = malloc(sizeof(char) * (len + 1));
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
