/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:15:16 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/07 21:17:41 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	var_name_len(char *arg)
{
	char	*delim;

	delim = ft_strchr(arg, '=');
	if (delim)
		return (delim - arg);
	return (ft_strlen(arg));
}

int	is_valid_varname(char *str)
{
	int	i;
	int	j;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
		i++;
	if (!(isalpha(str[0]) || str[0] == '_'))
		return (0);
	j = 1;
	while (j < i)
	{
		if (!(isalnum(str[j]) || str[j] == '_'))
			return (0);
		j++;
	}
	return (1);
}

void	sort_matrix(char **new_env)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = ft_matrixlen(new_env);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(new_env[j], new_env[j + 1]) > 0)
			{
				tmp = new_env[j];
				new_env[j] = new_env[j + 1];
				new_env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
