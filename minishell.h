/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:53:50 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/26 11:53:50 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "libft/libft.h"
#include "libraries/ft_printf/ft_printf.h"
#include "libraries/get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

typedef struct	s_path
{
	char	**path;
	int		size;
}				t_path;

int	g_exit;
void	ft_prompt();

#endif
