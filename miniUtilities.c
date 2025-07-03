/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniUtilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:34:15 by Dias              #+#    #+#             */
/*   Updated: 2025/07/03 16:03:44 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

t_mini	*create_mini(void)
{
	t_mini	*new_mini;

	new_mini = malloc(sizeof(t_mini));
	new_mini->env = NULL;
	new_mini->token = NULL;
	new_mini->cmd = NULL;
	return (new_mini);
}

void	reset_mini(t_mini *mini)
{
	mini->token = NULL;
	mini->cmd = NULL;
}
