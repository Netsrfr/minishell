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

//TODO: handle $NAME

void	ft_echo(char *line)
{
	char	*ptr;

	ptr = line;
	if (ft_strcmd(line, "echo") == 0)
	{
		line = line + 5;
		while (*line)
		{
			if (*line != '\'' && *line != '\"')
				write(1, line, 1);
			line++;
		}
		write(1, "\n", 1);
		free(ptr);
		exit(0);
	}
}

void	ft_clear(char *line)
{
	if (ft_strcmd(line, "clear") == 0 || (ft_strcmd(line, "cls") == 0))
	{
		ft_printf("\033[100H");
		ft_printf("\033[2J");
		exit(0);
	}
}

void	ft_prompt(void)
{
	char	*line;
	pid_t	pid;

	ft_printf("das_shell>>");
	if (!(get_next_line(0, &line)))
	{
		ft_printf("\n");
		ft_prompt();
	}
	ft_quotes(line);
	line = ft_home(line);
	ft_preprocessor(line);
	pid = fork();
	g_pid = pid;
	if (pid > 0)
		wait(&pid);
	else if (pid == 0)
	{
		ft_built_ins(line);
		exit(0);
	}
	free(line);
	ft_prompt();
}

int	main(void)
{
	signal(SIGINT, ft_signal);
	ft_printf("\033[100H");
	ft_printf("\033[2J");
	ft_prompt();
}
