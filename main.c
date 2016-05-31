/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 11:33:04 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/31 18:51:37 by dmoureu-         ###   ########.fr       */
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

int			putintcout(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

int	key_special(t_shell *shell, char *key)
{
	if (key[0] == 10 && key[1] == 0 && key[2] == 0 && key[3] == 0)
	{
		ft_putchar('\n');
		printtchar(shell->line);
		ft_putchar('\n');
		prompt();
		shell->line = NULL;
		shell->cur_pos = 0;
		return (1);
	}
	return (0);
}

void	key_arrow(t_shell *shell, char *key)
{
	(void)shell;
	if (key[0] == 27 && key[1] == 91 && key[3] == 0)
	{
		if (key[2] >= 65 && key[2] <= 68)
		{
			if (key[2] == 67 && shell->cur_pos < tcharlen(shell->line)) // right key
			{
				tputs(tgetstr("nd", NULL), 1, putintcout);
				shell->cur_pos++;
			}
			if (key[2] == 68 && shell->cur_pos > 0) // left key
			{
				tputs(tgetstr("le", NULL), 1, putintcout);
				shell->cur_pos--;
			}
		}
	}
}

void	key(t_shell *shell, char *key)
{
	t_chr	*new;
	int		use;

	use = 0;
	if (!key_special(shell, key))
	{
		key_arrow(shell, key);
		if (key[0] > 0 && key[1] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0)
		{
			if (shell->cur_pos == tcharlen(shell->line))
			{
				new = newtchar(key[0]);
				shell->line = addtchar(&shell->line, new);
				shell->cur_pos++;
				ft_putchar(key[0]);
			}
			else
			{
				new = newtchar(key[0]);
				shell->line = addtcharto(&shell->line, new, shell->cur_pos - 1);
				//debugtchar(shell->line);
				tputs(tgetstr("cd", NULL), 1, putintcout);
				ft_putchar(key[0]);
				shell->cur_pos++;
				printtcharfrom(shell->line, shell->cur_pos);
				use = tcharlenfrom(shell->line, shell->cur_pos);
				while (use > 0)
				{
					tputs(tgetstr("le", NULL), 1, putintcout);
					use--;
				}
			}
		}
	}
}

int		main(int ac, char **av, char **environ)
{
	//char	*line;
	t_shell	*shell;
	char	buffer[4];

	if (tgetent(NULL, "xterm-256color") == -1)
		perror("tgetent");
	(void)ac;
	(void)av;
	ft_bzero(buffer, 4);
	ft_signal();
	shell = newshell(environ);
	prompt();
	while (42)
	{
		//ft_printf("new while \n");

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
		//ft_printf(" %d %d %d %d \n", buffer[0], buffer[1], buffer[2], buffer[3]);
		key(shell, buffer);
		//printtchar(shell->line);
		ft_bzero(buffer, 4);
	}
}
