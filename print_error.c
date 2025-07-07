/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:51:07 by Dias              #+#    #+#             */
/*   Updated: 2025/07/07 13:54:59 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini.h"

int	g_status;

void	print_error(void)
{
	if (g_status == 400)
		printf("parse error near (pipe)\n");
	else if (g_status == 401)
		printf("parse error near (redirection)\n");
	else if (g_status == 402)
		printf("parse error near (quote)\n");
	else if (g_status == 403)
		printf("pipe creation error\n");
}
