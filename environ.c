/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 21:27:15 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/03 21:27:15 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_environ(void)
{
	extern char	**environ;
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (env);
}

void	ft_free_environ(char **env)
{
	char **ptr;

	ptr = env;
	while (*env)
	{
		free(*env);
		env++;
	}
	free(ptr);
}

static void	ft_parse_args(char *line)
{
	char **args;
	char **temp;

	args = ft_strsplit(&line[4], ' ');
	if (!(*args))
		ft_print();
	while (*args && ft_strchr(*args, '=') != 0)
	{
		temp = ft_strsplit(*args, '=');
		if (temp[2])
			ft_print_error("env: invalid argument:", *args);
		else
			setenv(temp[0], temp[1], 1);
		args++;
	}
}

void		ft_env_child(char *line)
{
	if (ft_strncmp(line, "env ", 4) == 0)
	{
		ft_parse_args(line);
		line = ft_strrchr(line, '=');
		if (!line)
		{
			ft_printf("usage: env [name=value...] [cammand] [arguments]");
			exit(0);
		}
		while (*line && *line != ' ')
			line++;
		if (*line != ' ')
			ft_print();
		else
			line++;
		ft_exec(line);
	}
}
