/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 11:03:52 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/06/03 11:03:52 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmd(char *line, char *cmd)
{
	char *temp;
	if (ft_strcmp(line, cmd) == 0)
		return (0);
	temp = ft_strjoin(cmd, " ");
	if (ft_strncmp(line, temp, ft_strlen(temp)) == 0)
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

void		ft_print_error(char *error)
{
	ft_printf("das shell: error: %s\n", error);
	exit(0);
}

char	*ft_add_path(char *argv0, char *argv1)
{
	char	*path;
	char	*temp;


	temp = ft_strjoin(argv0, "/");
	path = ft_strjoin(temp, argv1);
	free(temp);
	return (path);
}

void	ft_signal(int sig)
{
	printf("SIGNAL = %d\n", sig);
	if (sig == 2)
	{
		ft_printf("\nThank you for using the worlds most useless shell\n");
		exit(0);
	}
}

void	ft_print()
{
	extern char **environ;

	int i = 0;
	while(environ[i])
		ft_printf("%s\n", environ[i++]);
	exit(0);
}