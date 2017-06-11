/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:39:44 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/08 18:39:44 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_preprocessor(char **argv)
{
	ft_exit(argv[0]);
	ft_env(argv);
	ft_parse_setenv(argv);
	ft_parse_unsetenv(argv);
	ft_getenv(argv);
	ft_setpath(argv);
	ft_unsetpath(argv);
	ft_chdir(argv);
}

void	ft_built_ins(char **argv)
{
	argv = ft_env_child(argv);
	ft_echo(argv);
	ft_clear(argv[0]);
	ft_man(argv);
	ft_exec(argv);
}

void	ft_quotes(char *line)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if ((ft_strchr(line, '\'') != 0 || ft_strchr(line, '\"') != 0))
	{
		while (line[i])
		{
			if (line[i] == '\"')
				d++;
			if (line[i] == '\'')
				s++;
			i++;
		}
		if (d % 2 != 0 || s % 2 != 0)
		{
			ft_printe("das_shell: %s quote must be closed\n", CE);
			free(line);
			ft_prompt();
		}
	}
}

void	ft_expand_env(char *argv, int count)
{
	extern char	**environ;
	char		**temp;
	char		**env;
	int			i;

	i = 0;
	env = ft_environ();
	temp = ft_memalloc(sizeof(char*) * (count + 2));
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

void	ft_unset(int count, char *name)
{
	extern char	**environ;
	char		**temp;
	char		**env;
	char		**ptr;
	int			k;

	k = 0;
	env = ft_environ();
	ft_free_array(environ);
	ptr = env;
	temp = (char**)ft_memalloc(sizeof(char*) * (count));
	while (*env)
	{
		if (ft_strncmp(name, *env, ft_strlen(name)))
			temp[k++] = ft_strdup(*env);
		env++;
	}
	environ = temp;
	ft_free_array(ptr);
}
