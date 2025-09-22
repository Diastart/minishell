/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:19:49 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 16:20:13 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

char	*build_full_path(char *dir, char *cmd, t_mini *mini)
{
	char		*full_path;
	struct stat	st;

	full_path = malloc(strlen(dir) + 1 + strlen(cmd) + 1);
	if (!full_path)
		return (NULL);
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	if (stat(full_path, &st) != 0)
		return (NULL);
	if (S_ISDIR(st.st_mode))
		return (NULL);
	if (access(full_path, X_OK) != 0)
		return (NULL);
	mini->exit_status = 0;
	return (full_path);
}

char	**get_path_dirs(char **env)
{
	char	*path_env;
	char	*path_copy;
	char	**dirs;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dirs = ft_split(path_copy, ':');
	free(path_copy);
	return (dirs);
}

char	*find_command_in_path(t_mini *mini, char *cmd)
{
	char	**dirs;
	char	*full_path;
	size_t	i;

	if (!mini || !mini->cmd || !mini->cmd->args || !mini->cmd->args[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	dirs = get_path_dirs(mini->env);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = build_full_path(dirs[i], cmd, mini);
		if (full_path)
		{
			free_env(dirs);
			return (full_path);
		}
		i++;
	}
	free_env(dirs);
	mini->exit_status = 127;
	return (NULL);
}
