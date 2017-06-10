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

static void	ft_getenv(char **argv)
{
	char	*env;
	int		i;

	i = 1;
	if (ft_strcmd(argv[0], "getenv") == 0)
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

void		ft_preprocessor(char **argv)
{
	ft_exit(argv[0]);
	ft_env(argv);
	ft_setenv(argv);
	ft_getenv(argv);
	ft_unsetenv(argv);
	ft_chdir(argv);
}

//void		ft_man(char **argv)
//{
//	char	*path;
//	char	*temp;
//
//	if (ft_strcmp(argv[0], "man") == 0)
//	{
//		temp = ft_strjoin(argv[0], ".1");
//		path = ft_strjoin("/nfs/2016/")
//	}
//}

void		ft_built_ins(char **argv)
{
	ft_env_child(argv);
	ft_echo(argv);
	ft_clear(argv[0]);
	ft_exec(argv);
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
