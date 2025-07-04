/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manifest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:52:52 by Dias              #+#    #+#             */
/*   Updated: 2025/07/04 15:34:40 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	manifest_tokens(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		if (lcltoken->type == TOKEN_ERROR)
		{
			printf("Unclosed quote string was manifested...your prompt was not executed\n");
			return (1);
		}
		lcltoken = lcltoken->next;
	}
	return (0);
}

int	manifest_redirs(t_mini *mini)
{
	t_cmd	*lclcmd;
	t_redir	*lclredir;

	lclcmd = mini->cmd;
	while (lclcmd != NULL)
	{
		lclredir = lclcmd->redir;
		while (lclredir != NULL)
		{
			if (lclredir->type != REDIR_PIPE && lclredir->filename == NULL)
			{
				printf("Unset redirection was manifested...your prompt was not executed\n");
				return (1);
			}
			lclredir = lclredir->next;
		}
		lclcmd = lclcmd->next;
	}
	return (0);
}
