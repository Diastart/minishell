/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:23:21 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 01:08:08 by Dias             ###   ########.fr       */
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

void	redircase(t_token **rmttoken, t_cmd *cmd)
{

}

void	split_tokens_to_cmds(t_token **rmttoken, t_cmd *cmd)
{
	while ((*rmttoken) != NULL)
	{
		if ((*rmttoken)->type == TOKEN_WORD)
			wordcase(rmttoken, cmd);
		else if ((*rmttoken)->type == TOKEN_PIPE)
		{
			*rmttoken = (*rmttoken)->next;
			return ;
		}
		else
			redircase(rmttoken, cmd);
		// You stopped here redircase
		// Do not fotget rewrite all the code from beginning
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
