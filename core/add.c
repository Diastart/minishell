/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:01:37 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 17:54:22 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**create(int len)
{
	char	**new_listofstr;

	new_listofstr = malloc(sizeof(char *) * (len + 1 + 1));
	if (new_listofstr == NULL)
		return (NULL);
	new_listofstr[len + 1] = NULL;
	return (new_listofstr);
}

char	**add(char *str, char **listofstr)
{
	int		i;
	int		len;
	char	**new_listofstr;

	len = ft_listlen(listofstr);
	new_listofstr = create(len);
	i = 0;
	while (i < len)
	{
		new_listofstr[i] = listofstr[i];
		i++;
	}
	free(listofstr);
	new_listofstr[i] = ft_strdup(str);
	return (new_listofstr);
}
