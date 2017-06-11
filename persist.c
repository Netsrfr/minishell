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

void	ft_unsetenv(char *name)
{
	char		**env;
	char		*temp;
	int			i;

	env = ft_environ();
	i = 0;
	temp = ft_strjoin(name, "=");
	while (env[i] && ft_strncmp(temp, env[i], ft_strlen(temp)) != 0)
		i++;
	if (env[i] && ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
	{
		while (env[i])
			i++;
		ft_unset(i, name);
	}
	ft_free_array(env);
	free(temp);
}

void	ft_setenv(char *name, char *value, int cont)
{
	extern char	**environ;
	char		*temp;
	char		*ev;
	int			i;

	i = 0;
	temp = ft_strjoin(name, "=");
	ev = ft_strjoin(temp, value);
	while (environ[i] && ft_strncmp(environ[i], temp, ft_strlen(temp)) != 0)
		i++;
	if (environ[i] && ft_strncmp(environ[i], temp, ft_strlen(temp)) == 0)
	{
		free(environ[i]);
		environ[i] = ft_strdup(ev);
	}
	else
	{
		ft_expand_env(ev, i);
	}
	free(temp);
	free(ev);
	if (cont == 0)
		ft_prompt();
}

void	ft_env(char **argv)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (ft_strcmp(argv[0], "env") == 0 && (!argv[1]))
	{
		while (environ[i])
			ft_printf("%s\n", environ[i++]);
		ft_free_array(argv);
		ft_prompt();
	}
}

void	ft_parse_unsetenv(char **argv)
{
	if (ft_strcmp(argv[0], "unsetenv") == 0)
	{
		argv++;
		while (*argv)
		{
			if (ft_strchr(*argv, '=') != 0)
				ft_printe("das_shell: %s unsetenv: invalid argument: %s\n",
						CE, *argv);
			else if (ft_strcmp(*argv, "PATH") == 0)
				ft_setenv("PATH", "(null)", 0);
			else
				ft_unsetenv(*argv);
			free(*argv);
			argv++;
		}
		ft_prompt();
	}
}

void	ft_parse_setenv(char **argv)
{
	char	**env;
	int		i;

	i = 0;
	if (ft_strcmp(argv[0], "setenv") == 0)
	{
		if (!argv[1] || argv[2])
			ft_printe("%s setenv [name=value]\n", CU);
		else
		{
			env = ft_strsplit(argv[1], '=');
			while (env[i])
				i++;
			if (i != 2)
			{
				ft_printe("%s setenv [name=value]\n", CU);
				ft_free_array(argv);
				ft_prompt();
			}
			else
				ft_setenv(env[0], env[1], 1);
		}
		ft_free_array(argv);
		ft_prompt();
	}
}
