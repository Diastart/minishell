/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none_error_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:43:29 by Dias              #+#    #+#             */
/*   Updated: 2025/07/02 17:06:00 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	any_error_tokens(t_mini *mini)
{
	t_token	*local_token;

	local_token = mini->token;
	while (local_token != NULL)
	{
		if (local_token->type == TOKEN_ERROR)
			return (1);
		local_token = local_token->next;
	}
	return (0);
}
