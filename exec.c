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

void	ft_exec_path(char **argv, char **environ, char *cwd)
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
		temp = ft_add_path(*path, argv[0]);
		while (*path)
		{
			if (execve(temp, argv, environ) != -1)
				exit(0);
			free(temp);
			path++;
			if ((!(*path)))
				ft_print_error("command not found:", argv[0]);
			temp = ft_add_path(*path, argv[0]);
		}
	}
	exit(0);
}

void	ft_exec(char *line)
{
	char		*cwd;
	extern char	**environ;
	char		**argv;

	cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	argv = ft_split_whitespaces(line);
//	while(*argv)
//		printf("ARGV = %s\n", *argv++);
	if (argv[0][0] != '/')
		ft_exec_path(argv, environ, cwd);
	else if (execve(argv[0], argv, environ) == -1)
		ft_print_error("command not found:", argv[0]);
}
