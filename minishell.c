/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:53:50 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/26 11:53:50 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <ncurses.h>
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
	return (1);
}


void	ft_exit(char *line)
{
	if (ft_strcmd(line, "exit") == 0)
		exit(0);
}

void	ft_echo(char *line)
{
	char	*ptr;

	ptr = line;
	if (ft_strcmd(line, "echo") == 0)
	{
		line = line + 5;
		ft_printf("%s\n", line);
		free(ptr);
	}
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

void	ft_clear(char *line)
{
	if (ft_strcmd(line, "clear") == 0 || (ft_strcmd(line, "cls") == 0))
		ft_printf("\033[1J");
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
			printf("name = %s\n", *name);
			if (ft_strchr(*name, '=') != 0)
				ft_printf("error: unsetenv: '%s' invalid argument\n", *name);
			else
				unsetenv(*name);
			free(*name);
			name++;
		}
		//free(name);
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
		if (i == 0)
		{
			ft_printf("error: setenv: no argument\n");
			exit(0);
		}
		else if (i != 2)
		{
			ft_printf("error: setenv: invalid argument\n");
			exit(0);
		}
		while (*env)
			free(*env);
		free(env);
		setenv(env[0], env[1], 1);
		ft_prompt();
	}
}

void	ft_getenv(char *line)
{
	char	*name;
	char	*env;

	if (ft_strcmd(line, "getenv") == 0)
	{
		line = line + 7;
		printf("line = %s\n", line);
		name = ft_strdup(line);
		if (ft_strchr(name, ' ') != 0)
			ft_printf("error: getenv: too many arguments\n");
		printf("name = %s\n", name);
		env = getenv(name);
		free(name);
		ft_printf("%s\n", env);
		ft_prompt();
	}
}

void	ft_prompt()
{
	char	*line;
	//extern char *environ;
	pid_t	pid;
	signal(SIGINT, ft_signal);

	ft_printf("das_shell>>");
	if(!(get_next_line(0, &line)))
	{
		ft_printf("\n");
		ft_prompt();
	}
	ft_exit(line);
	ft_setenv(line);
	ft_getenv(line);
	ft_unsetenv(line);
	pid = fork();
	if (pid > 0)
	{
		wait(&pid);
	}
	else if (pid == 0)
	{
		ft_echo(line);
		ft_clear(line);
		exit(0);
	}
	free(line);
	ft_prompt();

}
int	main(int argc, char **argv, char **envp)
{
//	t_path path;
//	pid_t test;
	char *env;
	char *cwd;
	//env = getenv("PATH");
	signal(SIGINT, ft_signal);
	char *line;
	cwd = getcwd(cwd, PATH_MAX);
	//execve("/bin/lsth", &argv[0], NULL);
	env = getenv("TESTENV");

	printf("\033[50H");
	ft_printf("\033[1J");

	ft_prompt();
	return (0);
}
