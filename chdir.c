/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:37:32 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/08 17:37:32 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_pwd(char *cwd)
{
	setenv("OLDPWD", cwd, 1);
	setenv("PWD", getcwd(cwd, PATH_MAX), 1);
}

static void	ft_chdir_home(char *line)
{
	char	**env;
	char	***ptr;
	char	*cwd;

	cwd = ft_memalloc(PATH_MAX);
	ptr = ft_memalloc(sizeof(char**));
	env = ft_environ();
	*ptr = env;
	while (*env && ft_strncmp(*env, "HOME=", 5) != 0)
		env++;
	if (*env && ft_strncmp(*env, "HOME=", 5) == 0)
	{
		cwd = getcwd(cwd, PATH_MAX);
		if (chdir(&(*env)[5]) != -1)
			ft_set_pwd(cwd);
		free(cwd);
	}
	else
		ft_print_error("HOME not set path must be specified", "");
	ft_free_environ(*ptr);
	free(ptr);
	free(line);
	ft_prompt();
}

static char	*ft_oldpwd(void)
{
	char	***ptr;
	char	**env;
	char	*oldpwd;

	ptr = ft_memalloc(sizeof(char**));
	env = ft_environ();
	*ptr = env;
	while (*env && ft_strncmp(*env, "OLDPWD=", 7) != 0)
		env++;
	oldpwd = ft_strdup(&(*env)[7]);
	ft_free_environ(*ptr);
	free(ptr);
	return (oldpwd);
}

static void	ft_chdir_oldpwd(char *line)
{
	char	*oldpwd;
	char	*cwd;

	if (ft_strcmp(line, "-") == 0)
	{
		cwd = ft_memalloc(PATH_MAX);
		oldpwd = ft_oldpwd();
		setenv("OLDPWD", getcwd(cwd, PATH_MAX), 1);
		setenv("PWD", oldpwd, 1);
		chdir(oldpwd);
		free(oldpwd);
		free(cwd);
	}
	else if (ft_strncmp(line, "- ", 2) == 0)
		ft_printe("das_shell: cd: string not in pwd\n");
	else
		ft_printe("das_shell: cd: no such file or directory: %s", line);
}

void		ft_chdir(char *line)
{
	char	*cwd;
	char	**args;

	if (ft_strcmp(line, "cd") == 0)
		ft_chdir_home(line);
	else if (ft_strncmp(line, "cd ", 3) == 0)
	{
		if (line[3] == '-')
			ft_chdir_oldpwd(&line[3]);
		else
		{
			cwd = ft_memalloc(PATH_MAX);
			cwd = getcwd(cwd, PATH_MAX);
			args = ft_strsplit(&line[3], ' ');
			if (args[1])
				ft_printe("das_shell: cd: too many arguments\n");
			else if (chdir(args[0]) != -1)
				ft_set_pwd(cwd);
			else
				ft_print_error("cd: no such file or directory:", args[0]);
			while (*args)
				free(*args++);
			free(cwd);
		}
		free(line);
		ft_prompt();
	}
}
