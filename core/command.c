/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:08 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 16:37:05 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_cmd	*create(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static t_cmd	*make_cmd(t_mini *mini)
{
	t_cmd	*lclcmd;
	t_cmd	*tailcmd;

	tailcmd = create();
	lclcmd = mini->cmd;
	if (lclcmd == NULL)
		mini->cmd = tailcmd;
	else
	{
		while (lclcmd->next != NULL)
			lclcmd = lclcmd->next;
		lclcmd->next = tailcmd;
	}
	return (tailcmd);
}

int	parser_flow(t_token **rmttoken, t_cmd *lclcmd)
{
	while ((*rmttoken) != NULL)
	{
		if ((*rmttoken)->type == TOKEN_WORD)
		{
			lclcmd->args = add((*rmttoken)->val, lclcmd->args);
			(*rmttoken) = (*rmttoken)->next;
		}
		else if ((*rmttoken)->type == TOKEN_PIPE)
		{
			(*rmttoken) = (*rmttoken)->next;
			return (OK);
		}
		else
		{
			if (redir(rmttoken, lclcmd) == KO)
				return (KO);
			else
				(*rmttoken) = (*rmttoken)->next->next;
		}
	}
	return (OK);
}

int	command_flow(t_mini *mini)
{
	t_token	*lcltoken;
	t_cmd	*lclcmd;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		lclcmd = make_cmd(mini);
		if (parser_flow(&lcltoken, lclcmd) == KO)
			return (KO);
	}
	return (OK);
}
