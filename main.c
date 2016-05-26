/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 11:33:04 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/26 18:33:07 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>

void	sig_handler(int echo)
{
	if (echo == SIGINT)
	{
		exit(0);
	}
}

void	ft_signal(void)
{
	int		i;

	i = 0;
	while (i < 33)
	{
		if (i == SIGINT)
			signal(i, sig_handler);
		i++;
	}
}

void	execcommand(char *line, t_shell *shell)
{
	pid_t	father;

	if (ft_strchr(line, '~'))
		line = ft_strrepchrbystr(line, '~', envgetkey(shell->env, "HOME"));
	if (!builtin(shell, line))
	{
		father = fork();
		if (father > 0)
		{
			wait(&father);
		}
		else if (father == 0)
		{
			command(shell, line);
			exit(EXIT_SUCCESS);
		}
	}
}

int		main(int ac, char **av, char **environ)
{
	//char	*line;
	t_shell	*shell;
	char	buffer[4];

	(void)ac;
	(void)av;
	ft_bzero(buffer, 4);
	ft_signal();
	shell = newshell(environ);
	while (42)
	{
		ft_printf("new while \n");
		//prompt();
		/*
		if (!get_next_line(0, &line))
		{
			ft_printf("\n");
			exit(EXIT_SUCCESS);
		}
		line = ft_strrepchr(line, '\t', ' ');
		if (line)
		{
			execcommand(line, shell);
			free(line);
			line = NULL;
		}
		else
			exit(EXIT_FAILURE);
		*/
		read(0, buffer, 4);
		ft_printf(" %d %d %d %d \n",
		buffer[0], buffer[1], buffer[2], buffer[3]);
		ft_bzero(buffer, 4);
	}
}
