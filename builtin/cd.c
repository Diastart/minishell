/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonacco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:40:49 by ebonacco          #+#    #+#             */
/*   Updated: 2025/09/06 15:41:26 by ebonacco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

char	*resolve_cd_path(char **env, char **args)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD");
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_env_value(env, "HOME"));
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!oldpwd)
		{
			ft_putstr_fd(BASH_ERROR "cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putstr_fd(oldpwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (oldpwd);
	}
	return (args[1]);
}

void	set_env_value(char **env, char *key, char *value)
{
	char	*new_var;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(key);
	new_var = malloc(len + 1 + ft_strlen(value) + 1);
	if (!new_var)
		return ;
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return ;
		}
		i++;
	}
	env[i] = new_var;
	env[i + 1] = NULL;
}

char	*get_env_value(char **env, char *key)
{
	int		len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_cd(t_mini *mini)
{
	char	**args;
	char	**env;
	char	cwd[PATH_MAX];
	char	*path;
	char	*old_pwd;

	args = mini->cmd->args;
	env = mini->env;
	if (args[2])
		return (ft_putstr_fd(BASH_ERROR "cd: too many arguments\n", 2), 1);
	path = resolve_cd_path(env, args);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (perror(BASH_ERROR "cd"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror(BASH_ERROR "cd"), 1);
	old_pwd = get_env_value(env, "PWD");
	if (old_pwd)
		set_env_value(env, "OLDPWD", old_pwd);
	set_env_value(env, "PWD", cwd);
	return (0);
}
