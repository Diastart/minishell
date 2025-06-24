/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dias <dinursul@student.42.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:48:36 by Dias              #+#    #+#             */
/*   Updated: 2025/06/23 21:44:11 by Dias             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
#endif

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;

}				t_env;

typedef struct	s_mini
{
	t_env	*env;
}				t_mini;
