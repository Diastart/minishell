/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setCmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:23:21 by Dias              #+#    #+#             */
/*   Updated: 2025/07/04 15:31:56 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	get_args_size(char **cmdargs)
{
	int	args_size;

	args_size = 0;
	while (cmdargs != NULL && *cmdargs != NULL)
	{
		args_size++;
		cmdargs++;
	}
	return (args_size);
}

// +1 for new arg and +1 for terminator
char	**create_new_cmdargs(int args_size)
{
	char	**new_cmdargs;
	char	**head_new_cmdargs;

	new_cmdargs = malloc(sizeof(char *) * (args_size + 1 + 1));
	head_new_cmdargs = new_cmdargs;
	new_cmdargs += (args_size + 1);
	*new_cmdargs = NULL;
	return (head_new_cmdargs);
}

void	merge_arg_to_cmdargs(char *arg, t_cmd *cmd)
{
	char	**old_cmdargs;
	char	**new_cmdargs;
	char	**head_new_cmdargs;
	int		old_cmdargs_size;
	
	old_cmdargs = cmd->args;
	old_cmdargs_size = get_args_size(old_cmdargs);
	new_cmdargs = create_new_cmdargs(old_cmdargs_size);
	head_new_cmdargs = new_cmdargs;
	while (old_cmdargs != NULL && *old_cmdargs != NULL)
		*new_cmdargs++ = *old_cmdargs++;
	*new_cmdargs = arg;
	// free(cmd->args);
	cmd->args = head_new_cmdargs;
}

t_cmd	*create_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->args = NULL;
	new_cmd->redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*setget_tailcmd(t_mini *mini)
{
	t_cmd	*lclcmd;
	t_cmd	*tailcmd;

	tailcmd = create_cmd();
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

void	wordcase(t_token **rmttoken, t_cmd *cmd)
{
	char	*arg;

	arg = (*rmttoken)->val;
	merge_arg_to_cmdargs(arg, cmd);
	*rmttoken = (*rmttoken)->next;
}

t_redir	*create_redir(void)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	new_redir->filename = NULL;
	new_redir->type = REDIR_UNSET;
	new_redir->next = NULL;
	return (new_redir);
}

t_redir	*setget_tailredir(t_cmd *cmd)
{
	t_redir	*lclredir;
	t_redir	*tailredir;

	tailredir = create_redir();
	lclredir = cmd->redir;
	if (lclredir == NULL)
		cmd->redir = tailredir;
	else
	{
		while (lclredir->next != NULL)
			lclredir = lclredir->next;
		lclredir->next = tailredir;
	}
	return (tailredir);
}

t_redir_type	get_redir_type(t_token_type token_type)
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

void	redircase(t_token **rmttoken, t_cmd *cmd)
{
	t_redir	*lclredir;

	lclredir = setget_tailredir(cmd);
	lclredir->type = get_redir_type((*rmttoken)->type);
	(*rmttoken) = (*rmttoken)->next;
	if (*rmttoken != NULL)
	{
		if ((*rmttoken)->type == TOKEN_WORD)
		{
			lclredir->filename = (*rmttoken)->val;
			(*rmttoken) = (*rmttoken)->next;
		}
	}
}

void	pipecase(t_token **rmttoken, t_cmd *cmd)
{
	t_redir	*lclredir;

	lclredir = setget_tailredir(cmd);
	lclredir->type = REDIR_PIPE;
	(*rmttoken) = (*rmttoken)->next;
}

void	split_tokens_to_cmds(t_token **rmttoken, t_cmd *cmd)
{
	while ((*rmttoken) != NULL)
	{
		if ((*rmttoken)->type == TOKEN_WORD)
			wordcase(rmttoken, cmd);
		else if ((*rmttoken)->type == TOKEN_PIPE)
		{
			pipecase(rmttoken, cmd);
			return ;
		}
		else
			redircase(rmttoken, cmd);
	}
}

void	set_cmds(t_mini *mini)
{
	t_token	*lcltoken;
	t_cmd	*lclcmd;

	lcltoken = mini->token;
	while (lcltoken != NULL)
	{
		lclcmd = setget_tailcmd(mini);
		split_tokens_to_cmds(&lcltoken, lclcmd);
	}
}
