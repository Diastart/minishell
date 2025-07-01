/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:54:00 by Dias              #+#    #+#             */
/*   Updated: 2025/07/01 12:49:10 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

// this is just helper to print token_type since token_type
// is not string but just numerates
static char *token_type_to_string(t_token_type type)
{
	if (type == TOKEN_WORD) return "TOKEN_WORD";
	if (type == TOKEN_PIPE) return "TOKEN_PIPE";
	if (type == TOKEN_REDIR_APPEND) return "TOKEN_REDIR_APPEND";
	if (type == TOKEN_REDIR_HEREDOC) return "TOKEN_REDIR_HEREDOC";
	if (type == TOKEN_REDIR_IN) return "TOKEN_REDIR_IN";
	if (type == TOKEN_REDIR_OUT) return "TOKEN_REDIR_OUT";
	if (type == TOKEN_QUOTE) return "TOKEN_QUOTE";
	if (type == TOKEN_ERROR) return "TOKEN_ERROR";
	return "UNKNOWN";
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	char	*line;
	t_env	*temp_env;
	t_token	*temp_token;

	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	mini->token = NULL;
	
	copy_envps(mini, envp);
	printf("------------------ENVIRONMENT---VARIABLES------------------\n");
	// debug printing of environment variables
	temp_env = mini->env;
	while (temp_env != NULL)
	{
		printf ("%s=%s\n", temp_env->key, temp_env->val);
		temp_env = temp_env->next;
	}
	//
	printf("-----------------------------------------------------------\n");
	while (42)
	{
		line = readline("$minishell> ");
		mini->token = NULL;
		printf("----------------TOKENS---BEFORE---EXPANSION----------------\n");
		make_tokens(mini, line);
		temp_token = mini->token;
		while (temp_token != NULL)
		{
			printf("%s:%s\n", temp_token->val, token_type_to_string(temp_token->type));
			temp_token = temp_token->next;
		}
		temp_token = mini->token;
		printf("-----------------------------------------------------------\n");
		quote_exp(mini);
		printf("----------------TOKENS---AFTER---EXPANSION-----------------\n");
		temp_token = mini->token;
		while (temp_token != NULL)
		{
			printf("%s:%s\n", temp_token->val, token_type_to_string(temp_token->type));
			temp_token = temp_token->next;
		}
		temp_token = mini->token;
		printf("-----------------------------------------------------------\n");
	}
}
