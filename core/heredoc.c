/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:58:40 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/20 15:29:33 by dinursul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*read_line_from_stdin(void)
{
	char	buffer[1024];
	char	*line;
	int		bytes_read;
	int		i;

	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	i = 0;
	while (i < bytes_read && buffer[i] != '\n')
		i++;
	if (i < bytes_read)
		buffer[i] = '\0';
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strcpy(line, buffer);
	return (line);
}

static void	heredoc_child_loop(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = read_line_from_stdin();
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		heredoc_child_loop(pipefd[1], delimiter);
	else
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}
