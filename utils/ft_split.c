/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:16:07 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/08 11:17:38 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*str_copy(char *s, size_t n)
{
	char	*str;

	str = (char *)malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	return (str);
}

static char	*str_free(char **str, int k)
{
	while (k > 0)
		free(str[--k]);
	free(str);
	return (NULL);
}

static void	create_matrix(char **str, char *s, char c)
{
	int	i;
	int	k;
	int	j;

	j = 0;
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			j = i;
			while (s[i] && s[i] != c)
				i++;
			str[k] = str_copy(s + j, i - j);
			if (!str[k])
				str_free(str, k);
			k++;
		}
	}
	str[k] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	create_matrix(str, s, c);
	return (str);
}
