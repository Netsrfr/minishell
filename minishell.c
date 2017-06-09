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
		while(*line)
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

char	*ft_path_home(char *line)
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
		ft_printf("HOME not set path must be specified\n");
		free(line);
		ft_prompt();
	}
	home = ft_strdup(&(*env)[5]);
	ft_free_environ(*ptr);
	free(ptr);
	return(home);
}

char	*ft_insert_home(char *line, char *home, char *temp)
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
	return(line);
}

char	*ft_home(char *line)
{
	char	*temp;
	char	*home;
	int			i;
	int			count;

	if (ft_strchr(line, '~') != 0)
	{
		i = 0;
		count = 0;
		home = ft_path_home(line);
		while (line[i])
		{
			if (line[i] == '~')
				count++;
			i++;
		}
		temp = ft_memalloc(sizeof(char) * (count * ft_strlen(home) + ft_strlen(line)));
		line = ft_insert_home(line, home, temp);
	}
	return (line);
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

void	ft_quotes(char *line)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if (ft_strchr(line, '\'') != 0 || ft_strchr(line, '\"') != 0)
	{
		while (line[i])
		{
			if (line[i] == '\"')
				d++;
			if (line[i] == '\'')
				s++;
			i++;
		}
		if (d % 2 != 0 || s % 2 != 0)
		{
			ft_printf("das_shell: quote must be closed\n");
			free(line);
			ft_prompt();
		}
	}
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
	ft_quotes(line);
	line = ft_home(line);
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
