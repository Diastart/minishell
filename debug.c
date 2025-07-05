/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:36:22 by Dias              #+#    #+#             */
/*   Updated: 2025/07/05 18:33:06 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

char	*token_type_to_string(t_token_type token_type)
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
	if (token_type == TOKEN_QUOTE)
		return ("TOKEN_QUOTE");
	if (token_type == TOKEN_ERROR)
		return ("TOKEN_ERROR");
	return ("TOKEN_UNSET");
}

char	*redir_type_to_string(t_redir_type redir_type)
{
	if (redir_type == REDIR_IN)
		return ("REDIR_IN");
	else if (redir_type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (redir_type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (redir_type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else if (redir_type == REDIR_PIPE)
		return ("REDIR_PIPE");
	else
		return ("REDIR_UNSET");
}

void	print_envps(t_mini *mini)
{
	t_env	*lclenv;

	lclenv = mini->env;
	printf("----------------------------------\n");
	while (lclenv != NULL)
	{
		printf("%s=%s\n", lclenv->key, lclenv->val);
		lclenv = lclenv->next;
	}
	printf("----------------------------------\n");
}

void	print_tokens(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	printf("----------------------------------\n");
	while (lcltoken != NULL)
	{
		printf("%s : %s\n", lcltoken->val, token_type_to_string(lcltoken->type));
		lcltoken = lcltoken->next;
	}
	printf("----------------------------------\n");
}

void	print_redirs(t_cmd *rmtcmd)
{
	t_redir	*lclredir;

	lclredir = rmtcmd->redir;
	while (lclredir != NULL)
	{
		printf("(%s:%s) ", lclredir->filename, redir_type_to_string(lclredir->type));
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
