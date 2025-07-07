/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manifest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:52:52 by Dias              #+#    #+#             */
/*   Updated: 2025/07/07 13:55:23 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	g_status;

int	manifest_errtokens(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		if (lcltoken->type == TOKEN_ERROR)
		{
			g_status = 402;
			return (1);
		}
		lcltoken = lcltoken->next;
	}
	return (0);
}

int	manifest_nullredirs(t_mini *mini)
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
				g_status = 401;
				return (1);
			}
			lclredir = lclredir->next;
		}
		lclcmd = lclcmd->next;
	}
	return (0);
}

int	manifest_pipelast(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	if (lcltoken != NULL)
	{
		while (lcltoken->next != NULL)
			lcltoken = lcltoken->next;
		if (lcltoken->type == TOKEN_PIPE)
			return (1);
	}
	return (0);
}

int	manifest_consecpipes(t_mini *mini)
{
	t_token	*lcltoken;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		if (lcltoken->type == TOKEN_PIPE && lcltoken->next != NULL
		&& lcltoken->next->type == TOKEN_PIPE)
		{
			g_status = 400;
			return (1);
		}
		lcltoken = lcltoken->next;
	}
	return (0);
}

int	manifest_pipefirst(char *line)
{
	skip_whitespaces(&line);
	if (*line != '\0' && *line == '|')
	{
		g_status = 400;
		return (1);
	}
	return (0);
}
