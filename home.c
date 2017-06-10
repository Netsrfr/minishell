/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:36:13 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/08 18:36:13 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_path_home(char *line)
{
	char	**env;
	char	***ptr;
	char	*home;

	ptr = ft_memalloc(sizeof(char **));
	env = ft_environ();
	*ptr = env;
	while (*env && ft_strncmp(*env, "HOME=", 5) != 0)
		env++;
	if ((!*env) || ft_strncmp(*env, "HOME=", 5) != 0)
	{
		ft_printe("HOME not set path must be specified\n");
		free(line);
		ft_prompt();
	}
	home = ft_strdup(&(*env)[5]);
	ft_free_array(*ptr);
	free(ptr);
	return (home);
}

static char	*ft_insert_home(char *line, char *home, char *temp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '~')
		{
			k = 0;
			while (home[k])
				temp[j++] = home[k++];
			j--;
		}
		else
			temp[j] = line[i];
		j++;
		i++;
	}
	free(home);
	free(line);
	line = ft_strdup(temp);
	free(temp);
	return (line);
}

char		*ft_home(char *ln)
{
	char	*tmp;
	char	*home;
	int		i;
	int		c;

	if (ft_strchr(ln, '~') != 0)
	{
		i = 0;
		c = 0;
		home = ft_path_home(ln);
		while (ln[i])
		{
			if (ln[i] == '~')
				c++;
			i++;
		}
		tmp = ft_memalloc(sizeof(char) * (c * ft_strlen(home) + ft_strlen(ln)));
		ln = ft_insert_home(ln, home, tmp);
	}
	return (ln);
}
