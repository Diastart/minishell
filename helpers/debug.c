/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:36:22 by Dias              #+#    #+#             */
/*   Updated: 2025/07/10 17:19:59 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	g_status;

static char	*token_type_to_string(t_token_type token_type)
{
	if (token_type == TOKEN_WORD)
		return ("TOKEN_WORD");
	if (token_type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (token_type == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	if (token_type == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	if (token_type == TOKEN_REDIR_APPEND)
		return ("TOKEN_REDIR_APPEND");
	if (token_type == TOKEN_REDIR_HEREDOC)
		return ("TOKEN_REDIR_HEREDOC");
	return ("TOKEN_UNSET");
}

static char	*redir_type_to_string(t_redir_type redir_type)
{
	if (redir_type == REDIR_IN)
		return ("REDIR_IN");
	else if (redir_type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (redir_type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (redir_type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else
		return ("REDIR_UNSET");
}

void	print_tokens(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	printf("----------------------------------\n");
	while (lcltoken != NULL)
	{
		printf("%s : %s\n", lcltoken->val, \
			token_type_to_string(lcltoken->type));
		lcltoken = lcltoken->next;
	}
	printf("----------------------------------\n");
}

static void	print_redirs(t_cmd *rmtcmd)
{
	t_redir	*lclredir;

	lclredir = rmtcmd->redir;
	while (lclredir != NULL)
	{
		printf("(%s:%s) ", lclredir->filename, \
			redir_type_to_string(lclredir->type));
		lclredir = lclredir->next;
	}
}

void	print_cmds(t_mini *mini)
{
	t_cmd	*lclcmd;
	char	**lclargs;
	int		i;

	i = 1;
	lclcmd = mini->cmd;
	printf("----------------------------------\n");
	while (lclcmd != NULL)
	{
		printf("Command%d arguments: ", i);
		lclargs = lclcmd->args;
		while (lclargs != NULL && *lclargs != NULL)
		{
			printf("%s, ", (*lclargs));
			lclargs++;
		}
		printf("\n");
		printf("Command%d redirections: ", i);
		print_redirs(lclcmd);
		lclcmd = lclcmd->next;
		i++;
		printf("\n");
	}
	printf("----------------------------------\n");
}

void	print_status(void)
{
	if (g_status == 256)
		printf("pipe error\n");
	else if (g_status == 257)
		printf("quote error\n");
	else if (g_status == 258)
		printf("redir error\n");
}
