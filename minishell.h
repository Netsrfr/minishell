/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:53:50 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/26 11:53:50 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "libraries/ft_printf/ft_printf.h"
# include "libraries/get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

/*
** chdir.c
*/
void	ft_chdir(char *line);

/*
** environ.c
*/
void	ft_free_environ(char **env);
void	ft_env_child(char *line);
char	**ft_environ(void);

/*
** exec.c
*/
void	ft_exec(char *line);

/*
** helpers.c
*/
void	ft_preprocessor(char *line);
void	ft_built_ins(char *line);
void	ft_quotes(char *line);

/*
** home.c
*/
char	*ft_home(char *ln);

/*
** minishell.c
*/
void	ft_echo(char *line);
void	ft_clear(char *line);
void	ft_prompt(void);

/*
** persist.c
*/
void	ft_unsetenv(char *line);
void	ft_setenv(char *line);
void	ft_exit(char *line);
void	ft_env(char *line);

/*
** utility.c
*/
char	*ft_add_path(char *argv0, char *argv1);
int		ft_strcmd(char *line, char *cmd);
void	ft_print_error(char *error, char *arg);
void	ft_signal(int sig);
void	ft_print(void);

int		g_pid;
#endif
