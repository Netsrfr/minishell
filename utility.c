/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
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

void	ft_print_error(char *error, char *arg)
{
	ft_printf("das shell: error: %s %s\n", error, arg);
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
	if (sig == 2)
	{
		if (g_pid == 0)
			ft_printf("\ndas_shell>>");
		else
		{
			ft_printf("\n");
			kill(g_pid, SIGTERM);
			g_pid = 0;
		}
	}
}

void	ft_print(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
	exit(0);
}
