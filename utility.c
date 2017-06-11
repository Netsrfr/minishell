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

void	ft_exit(char *argv)
{
	if (ft_strcmp(argv, "exit") == 0)
		exit(0);
}

void	ft_print_error(char *error, char *arg)
{
	ft_printe("das_shell: %s %s %s\n", CE, error, arg);
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
