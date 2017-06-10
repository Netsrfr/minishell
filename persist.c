/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 09:57:34 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/03 09:57:34 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *argv)
{
	if (ft_strcmp(argv, "exit") == 0)
		exit(0);
}

//TODO: create unsetenv built-in

void	ft_unsetenv(char **argv)
{
	if (ft_strcmp(argv[0], "unsetenv") == 0)
	{
		argv++;
		while (*argv)
		{
			if (ft_strchr(*argv, '=') != 0)
				ft_printe("error: unsetenv: '%s' invalid argument\n", *argv);
			else if (ft_strcmp(*argv, "PATH") == 0)
				setenv("PATH", "(null)", 1);
			else
				unsetenv(*argv);
			free(*argv);
			argv++;
		}
		ft_prompt();
	}
}

static void ft_expand_env(char *argv, int count)
{
	char	**env;
	char	**temp;
	int		i;
	extern char **environ;


	ft_printf("count = %d\n", count);
	i = 0;
	env = ft_environ();
	temp = ft_memalloc(sizeof(char *) * count + 2);
	while (i < count)
	{
		temp[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	temp[i] = ft_strdup(argv);
	ft_free_array(environ);

	environ = temp;
	free(env);
}

void	ft_setenviron(char *argv, char *name)
{
	extern char	**environ;
	char		*temp;
	int i;

	i = 0;
	temp = ft_strjoin(name, "=");
	while (environ[i] && ft_strncmp(environ[i], temp, ft_strlen(temp)) != 0)
		i++;
	if (environ[i] && ft_strncmp(environ[i], temp, ft_strlen(temp)) == 0)
	{
		free(environ[i]);
		environ[i] = ft_strdup(argv);
	}
	else
	{
		ft_expand_env(argv, i);

	}
	free(temp);
	ft_prompt();
}

void	ft_setenv(char **argv)
{
	char	**env;
	int		i;

	i = 0;
	if (ft_strcmp(argv[0], "setenv") == 0)
	{
		if (!argv[1] || argv[2])
			ft_printe("usage: setenv [name=value]\n");
		else
		{
			env = ft_strsplit(argv[1], '=');
			while (env[i])
				i++;
			if (i != 2)
			{
				ft_printe("usage: setenv [name=value]\n");
				ft_free_array(argv);
				ft_prompt();
			}
			else
				//setenv(env[0], env[1], 1);
				ft_setenviron(argv[1], env[0]);
		}
		ft_free_array(argv);
		ft_prompt();
	}
}

void	ft_env(char **argv)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (ft_strcmp(argv[0], "env") == 0 && (!argv[1]))
	{
		//ptr = ft_memalloc(sizeof(char**));
		//*ptr = environ;
		while (environ[i])
			ft_printf("%s\n", environ[i++]);
		ft_free_array(argv);
		//environ = *ptr;
		//free(ptr);
		ft_prompt();
	}
}
