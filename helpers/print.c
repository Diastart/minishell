/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:07:25 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/18 22:07:30 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

void	print_stderr_syntax(char *str, t_mini *mini)
{
	ft_putstr_fd(BASH_ERROR "syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	mini->exit_status = 2;
}

void	print_stderr_cmd(char *str, t_mini *mini)
{
	(void)str;
	ft_putstr_fd(BASH_ERROR, STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	mini->exit_status = 127;
}

void	print_stderr_permission(char *str, t_mini *mini)
{
	(void)str;
	ft_putstr_fd(BASH_ERROR, STDERR_FILENO);
	ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	mini->exit_status = 126;
}

void	print_stderr_dir(char *str, t_mini *mini)
{
	(void)str;
	ft_putstr_fd(BASH_ERROR, STDERR_FILENO);
	ft_putstr_fd("Is a directory\n", STDERR_FILENO);
	mini->exit_status = 126;
}

void	print_stderr_file(char *str, t_mini *mini)
{
	(void)str;
	ft_putstr_fd(BASH_ERROR, STDERR_FILENO);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	mini->exit_status = 127;
}
