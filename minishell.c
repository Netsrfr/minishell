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
	//printf("SIGNAL = %d\n", sig);
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

void	ft_setenv(char *line)
{
	char **env;
	int i;

	i = 0;
	if (ft_strcmd(line, "setenv") == 0)
	{
		line = line + 6;
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
		setenv(env[0], env[1], 0);
	}
}

void	ft_getenv(char *line)
{
	char *name;

	if (ft_strcmd(line, "getenv") == 0)
	{
		line = line + 7;
		name = ft_strdup(line);
		if (ft_strchr(name, ' ') != 0)
			ft_printf("error: getenv: too many arguments\n");
	}
}

void	ft_prompt()
{
	char	*line;
	pid_t	pid;
	signal(SIGINT, ft_signal);
	wint_t key;

	ft_printf("das_shell>>");
	//key = getwchar();
	//printf("\033[1A");
//	if(key == 27)
//	{
//		key = getwchar();
//		if(key == 91)
//		{
//			key = getwchar();
//			if (key == 65)
//				printf("UP ARROW");
//		}
//	}
	//if (key == 27)
	//	printf("key = %d\n", key);
	get_next_line(0, &line);
	ft_exit(line);
	pid = fork();
	if (pid > 0)
	{
		wait(&pid);
	}
	else if (pid == 0)
	{
		ft_echo(line);
		ft_clear(line);
		ft_setenv(line);
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
	//signal(SIGINT, ft_signal);
	char *line;
	cwd = getcwd(cwd, PATH_MAX);
	printf("cwd = %s\n", cwd);
	//execve("/bin/lsth", &argv[0], NULL);
	env = getenv("TESTENV");
	printf("%s\n", env);

	//ft_printf("\033[1J");
	ft_prompt();
	return (0);
}
