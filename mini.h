/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:48:36 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:13:13 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#endif

extern int	g_exstat;

typedef enum	e_token_type
{
	TOKEN_UNSET,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_QUOTE,
	TOKEN_ERROR,
}				t_token_type;

typedef enum	e_redir_type
{
	REDIR_UNSET,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}				t_redir_type;

typedef struct	s_redir
{
	char			*filename;
	t_redir_type	type;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;

}				t_env;

typedef struct	s_token
{
	char			*val;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct	s_mini
{
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;
}				t_mini;

// Environment functions
char	*get_left_env(char *env_line);
char	*get_right_env(char *env_line);
t_env	*create_env(char *env_line);
void	connect_env(t_mini *mini, t_env *env);
void	copy_envps(t_mini *mini, char **envp);

// Debug functions
char	*token_type_to_string(t_token_type token_type);

// Expansion functions
char	*expand(t_env *env, char *envstr);
char	*rmv_quotes_and_expand(t_env *env, char *rmtval);
char	*search_and_expand(t_env *env, char *rmtval);
void	expansion(t_mini *mini);

// General utilities
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_dupsubstr(char *str_ptr, char *str_end);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_itoa(int status);
int		ft_intlen(int n);
int		is_alphanum(char c);
void	skip_envchrs(char **ptr);

// Mini utilities
t_mini	*create_mini(void);

// Command setting functions
int		get_args_size(char **cmdargs);
char	**create_new_cmdargs(int args_size);
void	merge_arg_to_cmdargs(char *arg, t_cmd *cmd);
t_cmd	*create_cmd(void);
t_cmd	*setget_tailcmd(t_mini *mini);
void	wordcase(t_token **rmttoken, t_cmd *cmd);
t_redir	*create_redir(void);
t_redir	*setget_tailredir(t_cmd *cmd);
t_redir_type	get_redir_type(t_token_type token_type);
void	redircase(t_token **rmttoken, t_cmd *cmd);
void	split_tokens_to_cmds(t_token **rmttoken, t_cmd *cmd);
void	set_cmds(t_mini *mini);

// Token utilities
t_token	*create_token(void);
t_token	*setget_tailtoken(t_mini *mini);
void	skip_whitespaces(char **line);
void	skip_untill_quote(char **line, char quote);
int		is_nspr(char c);
void	shift_if_spr_were_first(char *start, char **line);

// Tokenization functions
t_token_type	get_token_type_extra(char *token_val);
t_token_type	get_token_type(char *token_val);
char	*get_token_val(char **line);
void	pack_token(t_token *token, char **line);
void	tokenize(t_mini *mini, char *line);
void	reset_mini(t_mini *mini);


void	print_tokens(t_mini *mini);
void	print_commands(t_mini *mini);
void	print_envps(t_mini *mini);

