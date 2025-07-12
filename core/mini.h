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
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_status;

typedef enum e_redir_type
{
	REDIR_UNSET,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}				t_redir_type;

typedef struct s_last
{
	int		newline;
	char	*delim;
}				t_last;

typedef struct s_redir
{
	char			*filename;
	t_redir_type	type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

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

typedef struct s_token
{
	char			*val;
	t_token_type	type;
	int				state;
	struct s_token	*next;
}				t_token;

typedef struct s_mini
{
	char	**env;
	t_token	*token;
	t_cmd	*cmd;
}				t_mini;

int		pipe_first(char *line);
int		token_flow(t_mini *mini, char *line);
int		consec_pipes(t_mini *mini);
int		pipe_last(t_mini *mini);
int		command_flow(t_mini *mini);
int		parser_flow(t_token **rmttoken, t_cmd *lclcmd);
char	**add(char *str, char **listofstr);
int		redir(t_token **rmttoken, t_cmd *lclcmd);
int		ft_listlen(char **listofstr);
void	ft_putstr(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
char	*ft_substrdup(char	*str_ptr, char	*str_end);
void	skip_whitespaces(char **line);
void	skip_until_quote(char **line, char quote);
int		nspr(char c);
void	shift(char *start, char **line);
void	print_tokens(t_mini *mini);
void	print_cmds(t_mini *mini);
void	print_status(void);
void	free_flow(t_mini *mini, int env);
void	routing_flow(t_mini *mini);
void	update(t_token *lcltoken, t_mini *mini);
void	skip_envchrs(char **line);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_itoa(int status);

#endif