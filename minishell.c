/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:53:50 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/26 11:53:50 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		argv++;
		while (*argv)
		{
			if (*argv[0] == '$')
				ft_env_variable(*argv);
			else
			{
				while (**argv)
				{
					if (**argv != '\'' && **argv != '\"')
						write(1, *argv, 1);
					(*argv)++;
				}
			}
			write(1, " ", 1);
			argv++;
		}
		write(1, "\n", 1);
		exit(0);
	}
}

void		ft_clear(char *argv)
{
	if (ft_strcmp(argv, "clear") == 0 || (ft_strcmp(argv, "cls") == 0))
	{
		ft_printf("\033[100H");
		ft_printf("\033[2J");
		exit(0);
	}
}

static char	**ft_parse_line(char **line)
{
	char	**argv;
	int		i;

	i = 0;
	argv = NULL;
	ft_quotes(*line);
	*line = ft_home(*line);
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
		i++;
	if (i < (int)ft_strlen(*line))
	{
		*line = ft_strtrim(*line);
		argv = ft_split_whitespaces(*line);
	}
	free(*line);
	if (!argv)
		ft_prompt();
	return (argv);
}

void		ft_prompt(void)
{
	char	**argv;
	char	*line;
	pid_t	pid;

	ft_printf("das_shell>>");
	if (!(get_next_line(0, &line)))
	{
		ft_printf("\n");
		ft_prompt();
	}
	argv = ft_parse_line(&line);
	ft_preprocessor(argv);
	pid = fork();
	g_pid = pid;
	if (pid > 0)
		wait(&pid);
	else if (pid == 0)
	{
		ft_built_ins(argv);
		exit(0);
	}
	ft_prompt();
}

int			main(void)
{
	extern char		**environ;
	struct winsize	win;
	char			**env;

	env = ft_environ();
	environ = env;
	signal(SIGINT, ft_signal);
	ioctl(0, TIOCGWINSZ, &win);
	ft_printf("\033[100H");
	ft_printf("\033[2J");
	if (win.ws_col >= 140 && win.ws_row >= 27)
		ft_intro(win);
	ft_prompt();
}
