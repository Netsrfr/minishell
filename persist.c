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

void	ft_exit(char *line)
{
	if (ft_strcmd(line, "exit") == 0)
		exit(0);
}

void	ft_unsetenv(char *line)
{
	char **name;

	if (ft_strcmd(line, "unsetenv") == 0)
	{
		line = line + 9;
		name = ft_strsplit(line, ' ');
		while(*name)
		{
			if (ft_strchr(*name, '=') != 0)
				ft_printf("error: unsetenv: '%s' invalid argument\n", *name);
			else
				unsetenv(*name);
			free(*name);
			name++;
		}
		ft_prompt();
	}
}

void	ft_setenv(char *line)
{
	char **env;
	int i;

	i = 0;
	if (ft_strcmd(line, "setenv") == 0)
	{
		line = line + 7;
		env = ft_strsplit(line, '=');
		while (env[i])
			i++;
		if (i != 2)
		{
			ft_printf("usage: setenv [name=value]\n");
			free(env);
			ft_prompt();
		}
		else
			setenv(env[0], env[1], 1);
		while (*env)
			free(*env++);
		ft_prompt();
	}
}

void	ft_env(char *line)
{
	extern char **environ;
	char		***ptr;

	if (ft_strcmp(line, "env") == 0)
	{
		ptr = ft_memalloc(sizeof(char**));
		*ptr = environ;
		while (*environ && ft_printf("%s\n", *environ++));
		free(line);
		environ = *ptr;
		free(ptr);
		ft_prompt();
	}
}