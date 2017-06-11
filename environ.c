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

char		**ft_environ(void)
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

void		ft_free_array(char **env)
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

static void	ft_parse_args(char **argv)
{
	char **temp;

	if (!(argv[1]))
		ft_print();
	argv++;
	while (*argv && ft_strchr(*argv, '=') != 0)
	{
		temp = ft_strsplit(*argv, '=');
		if (temp[2])
			ft_print_error("env: invalid argument:", *argv);
		else
			ft_setenv(temp[0], temp[1], 1);
		argv++;
	}
}

char		**ft_env_child(char **argv)
{
	if (ft_strcmp(argv[0], "env") == 0)
	{
		ft_parse_args(argv);
		argv++;
		while (*argv && ft_strrchr(*argv, '='))
			argv++;
		ft_env_child(argv);
	}
	return (argv);
}

void		ft_env_variable(char *argv)
{
	char	*temp;
	char	**env;

	env = ft_environ();
	argv++;
	temp = ft_strdup(argv);
	while (ft_strncmp(*env, temp, ft_strlen(temp)) != 0)
		env++;
	if (ft_strncmp(*env, temp, ft_strlen(temp)) == 0)
		ft_printf("%s", &((*env)[ft_strlen(temp) + 1]));
}
