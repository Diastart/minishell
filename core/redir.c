/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dias <dias@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:02:09 by dias              #+#    #+#             */
/*   Updated: 2025/07/10 16:55:31 by dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/mini.h"

int	g_status;

static t_redir_type	convert(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	else
		return (REDIR_UNSET);
}

static t_redir	*create(void)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
		return (NULL);
	new_redir->filename = NULL;
	new_redir->type = REDIR_UNSET;
	new_redir->next = NULL;
	return (new_redir);
}

static t_redir	*make_redir(t_cmd *lclcmd)
{
	t_redir	*lclredir;
	t_redir	*tailredir;

	tailredir = create();
	lclredir = lclcmd->redir;
	if (lclredir == NULL)
		lclcmd->redir = tailredir;
	else
	{
		while (lclredir->next != NULL)
			lclredir = lclredir->next;
		lclredir->next = tailredir;
	}
	return (tailredir);
}

int	redir(t_token **rmttoken, t_cmd *lclcmd)
{
	t_redir	*lclredir;

	if ((*rmttoken)->next == NULL || (*rmttoken)->next->type != TOKEN_WORD)
	{
		g_status = 258;
		return (KO);
	}
	lclredir = make_redir(lclcmd);
	lclredir->type = convert((*rmttoken)->type);
	lclredir->filename = ft_strdup((*rmttoken)->next->val);
	return (OK);
}
