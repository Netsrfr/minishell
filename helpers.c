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

static void	ft_getenv(char *line)
{
	char	*name;
	char	*env;

	if (ft_strcmd(line, "getenv") == 0)
	{
		line = line + 7;
		name = ft_strdup(line);
		if (ft_strchr(name, ' ') != 0)
			ft_printe("error: getenv: too many arguments\n");
		env = getenv(name);
		free(name);
		ft_printf("%s\n", env);
		ft_prompt();
	}
}

void		ft_preprocessor(char *line)
{
	ft_exit(line);
	ft_env(line);
	ft_setenv(line);
	ft_getenv(line);
	ft_unsetenv(line);
	ft_chdir(line);
}

void	ft_built_ins(char *line)
{
	ft_env_child(line);
	ft_echo(line);
	ft_clear(line);
	ft_exec(line);
}

void		ft_quotes(char *line)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if (ft_strchr(line, '\'') != 0 || ft_strchr(line, '\"') != 0)
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
			ft_printe("das_shell: quote must be closed\n");
			free(line);
			ft_prompt();
		}
	}
}
