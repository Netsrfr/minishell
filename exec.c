/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 21:33:29 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/03 21:33:29 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_s_ixusr(char *argv, char **path)
{
	struct stat	stats;
	char		*temp;

	temp = ft_add_path(*path, argv);
	while (*path)
	{
		lstat(temp, &stats);
		if (S_ISREG(stats.st_mode) && (!(stats.st_mode & S_IXUSR)))
			ft_print_error("permission denied:", argv);
		free(temp);
		path++;
		if ((!(*path)))
			ft_print_error("command not found:", argv);
		temp = ft_add_path(*path, argv);
	}
}

static void	ft_run_path(char **path, char **argv, char **environ)
{
	char	**ptr;
	char	*temp;

	ptr = path;
	temp = ft_add_path(*path, argv[0]);
	while (*path)
	{
		if (execve(temp, argv, environ) != -1)
			exit(0);
		free(temp);
		path++;
		if ((!(*path)))
			ft_s_ixusr(argv[0], ptr);
		temp = ft_add_path(*path, argv[0]);
	}
}

static void	ft_exec_path(char **argv, char **environ, char *cwd)
{
	char	**path;
	char	*temp;

	temp = ft_add_path(cwd, argv[0]);
	if (execve(temp, argv, environ) == -1)
	{
		free(temp);
		while (*environ && ft_strncmp(*environ, "PATH=", 5) != 0)
			environ++;
		if (!(*environ))
			ft_print_error("command not found:", argv[0]);
		path = ft_strsplit(&(*environ)[5], ':');
		ft_run_path(path, argv, environ);
	}
	exit(0);
}

void		ft_exec(char **argv)
{
	extern char	**environ;
	struct stat	stats;
	char		*cwd;

	cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	if (ft_strncmp(argv[0], "\033", 1) == 0)
		exit(0);
	if (*argv[0] != '/')
		ft_exec_path(argv, environ, cwd);
	else if (execve(*argv, argv, environ) == -1)
	{
		lstat(argv[0], &stats);
		if (S_ISREG(stats.st_mode) && (!(stats.st_mode & S_IXUSR)))
			ft_print_error("permission denied:", argv[0]);
		else
			ft_print_error("command not found:", argv[0]);
	}
}
