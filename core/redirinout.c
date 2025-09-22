/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:27:38 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 17:31:09 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_redir(t_redir *lclredir, int fd, int nl)
{
	if (fd == -1)
	{
		if (lclredir->type == REDIR_IN || lclredir->type == REDIR_OUT
			|| lclredir->type == REDIR_APPEND)
			perror(lclredir->filename);
		exit(1);
	}
	if (lclredir->type == REDIR_OUT)
	{
		dup2(fd, STDOUT_FILENO);
		nl = 1;
	}
	else if (lclredir->type == REDIR_APPEND)
	{
		dup2(fd, STDOUT_FILENO);
		nl = 0;
	}
	else if (lclredir->type == REDIR_IN || lclredir->type == REDIR_HEREDOC)
	{
		dup2(fd, STDIN_FILENO);
		nl = 1;
	}
	close(fd);
	return (nl);
}

int	open_file(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_HEREDOC)
		fd = redir->heredoc_fd;
	else
		fd = -1;
	return (fd);
}

int	redirinout(t_cmd *lclcmd)
{
	int		fd;
	int		nl_stdout;
	t_redir	*lclredir;

	nl_stdout = 1;
	lclredir = lclcmd->redir;
	while (lclredir)
	{
		fd = open_file(lclredir);
		if (fd == -1)
		{
			perror(lclredir->filename);
			exit(1);
		}
		if (lclredir->type == REDIR_OUT || lclredir->type == REDIR_APPEND)
		{
			dup2(fd, STDOUT_FILENO);
			nl_stdout = 0;
		}
		else if (lclredir->type == REDIR_IN || lclredir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		close(fd);
		lclredir = lclredir->next;
	}
	return (nl_stdout);
}
