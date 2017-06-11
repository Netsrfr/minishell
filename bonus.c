/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 12:32:29 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/10 12:32:29 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_man(char **argv)
{
	extern char	**environ;
	struct stat	stats;
	char		*path;
	char		*temp;
	char		*file;

	if (ft_strcmp(argv[0], "man") == 0)
	{
		if (argv[1] && getenv("HOME"))
		{
			temp = ft_strjoin(argv[1], ".1");
			path = ft_strjoin(getenv("HOME"), "/bin/man/");
			file = ft_strjoin(path, temp);
			lstat(file, &stats);
			if (S_ISREG(stats.st_mode))
			{
				free(argv[1]);
				argv[1] = ft_strdup(file);
				execve("/usr/bin/man", argv, environ);
				exit(0);
			}
		}
	}
}

void	ft_getenv(char **argv)
{
	char	*env;
	int		i;

	i = 1;
	if (ft_strcmp(argv[0], "getenv") == 0)
	{
		while (argv[i])
		{
			if (!(env = getenv(argv[i])))
				ft_printe("das_shell: %s getenv: environment variable '%s' "
								"not found\n", CE, argv[i]);
			else
				ft_printf("%s\n", env);
			i++;
		}
		ft_prompt();
	}
}

void	ft_setpath(char **argv)
{
	if (ft_strcmp(argv[0], "setpath") == 0)
	{
		if (!argv[1] || argv[2])
			ft_printe("%s setpath [value]\n", CU);
		else
		{
			if (ft_strchr(argv[1], '=') != 0)
				ft_printe("das_shell %s input value only; PATH implied\n", CE);
			else if (ft_strcmp(argv[1], "default") == 0)
				ft_setenv("PATH", "/bin:/usr/bin", 1);
			else if (ft_strcmp(argv[1], "defense") == 0)
				ft_setenv("PATH", "/bin:/usr/bin:/tmp/bin", 1);
			else
				ft_setenv("PATH", argv[1], 1);
		}
		ft_free_array(argv);
		ft_prompt();
	}
}

void	ft_unsetpath(char **argv)
{
	if (ft_strcmp(argv[0], "unsetpath") == 0)
	{
		if (argv[1])
			ft_printe("%s unsetpath\n", CU);
		else
			ft_setenv("PATH", "(null)", 1);
		ft_free_array(argv);
		ft_prompt();
	}
}
