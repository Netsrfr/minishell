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

void	ft_exit(char *line)
{
	if (ft_strncmp(line, "exit ", 5) == 0 || ft_strcmp(line, "exit") == 0)
		exit(0);
}

void	ft_echo(char *line)
{
	char	*ptr;

	ptr = line;
	if (ft_strncmp(line, "echo", 4) == 0)
	{
		line = line + 5;
		ft_printf("%s\n", line);
		//free(ptr);
	}
}

void	ft_signal(int sig)
{
	printf("SIGNAL = %d\n", sig);
	if (sig == 2)
		exit(0);
}

void	ft_clear(char *line)
{

}


void	ft_prompt()
{
	char	*line;
	pid_t	pid;
	signal(SIGINT, ft_signal);

	ft_printf("das_shell>>");
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
		exit(0);
	}
	free(line);
	ft_prompt();
}

int	main(int argc, char **argv, char **envp)
{
	t_path path;
	pid_t test;

	//signal(SIGINT, ft_signal);
	char *line;

	//execve("/bin/lsth", &argv[0], NULL);


		ft_prompt();
		free(line);
		if (g_exit == 0)
			main(argc, argv, envp);
//	char clear [ 5 ] = { 27, '[', '2', 'J', 0 };
//	printf ( "%s", clear );
	//printf("\033[2J");


printf("TEST\n");

	return (0);
}
