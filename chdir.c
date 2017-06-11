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
	ft_setenv("OLDPWD", cwd, 1);
	ft_setenv("PWD", getcwd(cwd, PATH_MAX), 1);
}

static void	ft_chdir_home(char **argv)
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
		ft_printe("das_shell: %s cd: HOME not set path must be specified\n",
				CE);
	ft_free_array(*ptr);
	free(ptr);
	ft_free_array(argv);
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
	ft_free_array(*ptr);
	free(ptr);
	return (oldpwd);
}

static void	ft_chdir_oldpwd(char **argv)
{
	char	*oldpwd;
	char	*cwd;

	if (!argv[2])
	{
		cwd = ft_memalloc(PATH_MAX);
		oldpwd = ft_oldpwd();
		ft_setenv("OLDPWD", getcwd(cwd, PATH_MAX), 1);
		ft_setenv("PWD", oldpwd, 1);
		chdir(oldpwd);
		ft_printf("%s\n", oldpwd);
		free(oldpwd);
		free(cwd);
	}
	else
		ft_printe("das_shell: %s cd: string not in pwd\n", CE);
}

void		ft_chdir(char **argv)
{
	char	*cwd;

	if (ft_strcmp(argv[0], "cd") == 0 && (!argv[1]))
		ft_chdir_home(argv);
	else if (ft_strcmp(argv[0], "cd") == 0 && (argv[1]))
	{
		if (ft_strcmp(argv[1], "-") == 0)
			ft_chdir_oldpwd(argv);
		else
		{
			cwd = ft_memalloc(PATH_MAX);
			cwd = getcwd(cwd, PATH_MAX);
			if (argv[2])
				ft_printe("das_shell: %s cd: too many arguments\n", CE);
			else if (chdir(argv[1]) != -1)
				ft_set_pwd(cwd);
			else
				ft_printe("das_shell: %s cd: no such file or directory: %s\n",
						CE, argv[1]);
			free(cwd);
		}
		ft_free_array(argv);
		ft_prompt();
	}
}
