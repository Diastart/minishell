/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:04:43 by dias              #+#    #+#             */
/*   Updated: 2025/07/12 20:17:07 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# define KO 1
# define OK 0
# define ENV 2
# define NOENV 3
# define READ_KEY 0
# define WRITE_KEY 1
# define TERMINAL -1
# define BASH "$dias_eugenio_shell> "
# define BASH_ERROR "$dias_eugenio_shell: "
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_status;

typedef enum e_redir_type
{
	REDIR_UNSET,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}				t_redir_type;

typedef enum e_token_type
{
	TOKEN_UNSET,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
}				t_token_type;

typedef struct s_last
{
	int		newline;
	char	*delim;
}				t_last;

typedef struct s_redir
{
	char			*filename;
	int				heredoc_fd;
	t_redir_type	type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*val;
	int				state;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_mini
{
	char	**env;
	int		exit_status;
	t_token	*token;
	t_cmd	*cmd;
}				t_mini;

char	**add(char *str, char **listofstr);
void	add_update_new_vars(char **new_env, char **args);
int		builtin_cd(t_mini *mini);
int		builtin_echo(t_cmd *cmd);
int		builtin_env(t_mini *mini, t_cmd *cmd);
int		builtin_exit(t_mini *mini);
int		builtin_export(t_mini *mini);
int		builtin_pwd(void);
int		builtin_unset(t_mini *mini);
void	child(int pipefd[2], int carry, t_cmd *cmd, t_mini *mini);
int		command_flow(t_mini *mini);
int		consec_pipes(t_mini *mini);
int		exec_builtin(t_cmd *cmd, t_mini *mini);
int		exec_command(t_mini *mini, t_cmd *cmd, int *carry, pid_t *last_pid);
int		exec_single_builtin(t_mini *mini, t_cmd *cmd);
char	*find_command_in_path(t_mini *mini, char *cmd);
void	free_env(char **env);
void	free_flow(t_mini *mini, int env);
char	*ft_itoa(int status);
int		ft_atoi(const char *nptr);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_listlen(char **listofstr);
int		ft_matrixlen(char **str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_strjoin_tmp(char *res, char *tmp, int free_res);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlen(char *str);
size_t	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strspn(const char *str, const char *accept);
char	*ft_substrdup(char	*str_ptr, char	*str_end);
char	*get_env_value(char **env, char *key);
int		handle_heredoc(char *delimiter);
int		has_redir_in(t_cmd *cmd);
int		has_redir_out(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
int		is_numeric(const char *str);
int		is_valid_varname(char *str);
char	*join_search(t_mini *mini, char *res, char *start, char *end);
int		nspr(char c);
void	parent(int pipefd[2], int *carry, t_cmd *cmd);
int		parser_flow(t_token **rmttoken, t_cmd *lclcmd);
int		pipe_first(char *line);
int		pipe_last(t_mini *mini);
void	print_cmds(t_mini *mini);
void	print_status(void);
void	print_stderr_args(char *str);
void	print_stderr_cmd(char *str, t_mini *mini);
void	print_stderr_dir(char *str, t_mini *mini);
void	print_stderr_exit(char *str);
void	print_stderr_export(char *str);
void	print_stderr_file(char *str, t_mini *mini);
void	print_stderr_permission(char *str, t_mini *mini);
void	print_stdout(char *str);
void	print_tokens(t_mini *mini);
int		redir(t_token **rmttoken, t_cmd *lclcmd);
int		redirinout(t_cmd *lclcmd);
int		routing_flow(t_mini *mini);
char	*search(t_mini *mini, char *val);
char	*search_free(t_mini *mini, char *tmp);
void	set_signals(void);
void	set_signals(void);
void	shift(char *start, char **line);
void	skip_envchrs(char **line);
void	skip_until_quote(char **line, char quote);
void	skip_whitespaces(char **line);
char	*search_free(t_mini *mini, char *tmp);
char	*search(t_mini *mini, char *val);
void	sort_matrix(char **new_env);
int		token_flow(t_mini *mini, char *line);
int		trash(t_cmd *cmd, t_mini *mini, char *cmd_path);
int		under_flow(t_mini *mini);
char	*unquote(t_mini *mini, char *val);
void	update(t_token *lcltoken, t_mini *mini);
int		var_name_len(char *arg);
void	validate_and_exec_cmd(t_mini *mini, t_cmd *cmd, char *cmd_path);

#endif
