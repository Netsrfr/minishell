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



void	ft_echo(char *line)
{
	char	*ptr;

	ptr = line;
	if (ft_strcmd(line, "echo") == 0)
	{
		line = line + 5;
		ft_printf("%s\n", line);
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

void	ft_getenv(char *line)
{
	char	*name;
	char	*env;

	if (ft_strcmd(line, "getenv") == 0)
	{
		line = line + 7;
		name = ft_strdup(line);
		if (ft_strchr(name, ' ') != 0)
			ft_printf("error: getenv: too many arguments\n");
		env = getenv(name);
		free(name);
		ft_printf("%s\n", env);
		ft_prompt();
	}
}

void	ft_preprocessor(char *line)
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

void	ft_prompt()
{
	char	*line;
	pid_t	pid;
	signal(SIGINT, ft_signal);

	ft_printf("das_shell>>");
	if(!(get_next_line(0, &line)))
	{
		ft_printf("\n");
		ft_prompt();
	}
	ft_preprocessor(line);
	pid = fork();
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

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, ft_signal);
	ft_printf("\033[100H");
	ft_printf("\033[2J");
	ft_prompt();
}
