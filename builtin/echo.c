/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:42:33 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:42:44 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	builtin_echo(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		newline;

	args = cmd->args;
	i = 1;
	newline = 1;
	while ((args[i] && !ft_strncmp(args[i], "-n", 2))
		&& ft_strspn(args[i] + 2, "n") == ft_strlen(args[i] + 2))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
