/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:48:36 by Dias              #+#    #+#             */
/*   Updated: 2025/07/01 12:31:23 by Dias             ###   ########.fr       */
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

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_QUOTE,
	TOKEN_ERROR,
}				t_token_type;

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
}				t_mini;

char	*get_left_env(char *env_line);
char	*get_right_env(char *env_line);
t_env	*create_env(char *env_line);
void	connect_env(t_mini *mini, t_env *env);
void	copy_envps(t_mini *mini, char **envp);
void	make_tokens(t_mini *mini, char *line);
void	connect_token(t_mini *mini, t_token *token);
t_token	*create_token(char **line);
char	*get_token_value(char **line);
int		slen(char *s);
int		cmpr(char *s1, char *s2);
t_token_type	get_token_type_extra(char *token_val);
t_token_type	get_token_type(char *token_val);
char	*subdup(char *s1, char *s2);
int		is_alphanum(char c);
char	*env_exp(t_mini *mini, char *s);
char	*merge(char *s1, char *s2);
char	*dquote(t_mini *mini, char *s);
void	update(t_mini *mini, t_token *current);
void	quote_exp(t_mini *mini);
