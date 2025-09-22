/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:08:17 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/18 22:08:19 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

void	print_stderr_exit(char *str)
{
	ft_putstr_fd(BASH_ERROR "exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	print_stderr_export(char *str)
{
	ft_putstr_fd(BASH_ERROR "export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_stderr_args(char *str)
{
	(void)str;
	ft_putstr_fd(BASH_ERROR "exit: ", STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}

void	print_stdout(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
