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
# include "libraries/ft_printe/ft_printe.h"
# include "libraries/get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# define CE ("\x1b[31merror:\x1b[39m")
# define CU ("\x1b[37musage:\x1b[39m")

/*
** bonus.c
*/
void	ft_unsetpath(char **argv);
void	ft_setpath(char **argv);
void	ft_getenv(char **argv);
void	ft_man(char **argv);

/*
** chdir.c
*/
void	ft_chdir(char **argv);

/*
** environ.c
*/
void	ft_free_array(char **env);
void	ft_env_variable(char *argv);
char	**ft_env_child(char **argv);
char	**ft_environ(void);

/*
** exec.c
*/
void	ft_exec(char **argv);

/*
** helpers.c
*/
void	ft_expand_env(char *argv, int count);
void	ft_unset(int count, char *name);
void	ft_preprocessor(char **argv);
void	ft_built_ins(char **argv);
void	ft_quotes(char *line);

/*
** home.c
*/
char	*ft_home(char *ln);

/*
** intro.c
*/
void	ft_intro(struct winsize win);

/*
** minishell.c
*/
void	ft_echo(char **argv);
void	ft_clear(char *argv);
void	ft_prompt(void);

/*
** persist.c
*/
void	ft_setenv(char *name, char *value, int cont);
void	ft_parse_unsetenv(char **argv);
void	ft_parse_setenv(char **argv);
void	ft_unsetenv(char *name);
void	ft_env(char **argv);

/*
** utility.c
*/
char	*ft_add_path(char *argv0, char *argv1);
void	ft_print_error(char *error, char *arg);
void	ft_exit(char *argv);
void	ft_signal(int sig);
void	ft_print(void);

int		g_pid;
#endif
