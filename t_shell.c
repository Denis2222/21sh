/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 22:06:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/31 18:00:56 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			putintc(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void	updateshell(t_shell *shell)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	shell->sz->ws_col = w.ws_col;
	shell->sz->ws_row = w.ws_row;
}

void	selectmodeon(t_shell *shell)
{
	if (tcsetattr(0, TCSADRAIN, shell->tios) == -1)
		perror("tcsetattr error");
}

void	selectmodeoff(t_shell *shell)
{
	tcsetattr(0, TCSADRAIN, shell->tiosold);
}

t_shell	*newshell(char **environ)
{
	t_shell	*shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	shell->env = loadenv(environ);
	shell->envtxt = genenv(shell->env);
	shell->sz = (struct winsize*)malloc(sizeof(struct winsize));
	ioctl(0, TIOCGWINSZ, shell->sz);
	shell->tiosold = (struct termios*)malloc(sizeof(struct termios));
	shell->tios = (struct termios*)malloc(sizeof(struct termios));
	if (tcgetattr(0, shell->tiosold) == -1)
		return (NULL);
	tcgetattr(0, shell->tios);
	shell->tios->c_lflag &= ~(ICANON);
	shell->tios->c_lflag &= ~(ECHO);
	shell->tios->c_cc[VMIN] = 1;
	shell->tios->c_cc[VTIME] = 0;
	shell->cur_pos = 0;
	selectmodeon(shell);
	return (shell);
}

void	shell_env_refresh(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envtxt[i])
	{
		free(shell->envtxt[i]);
		i++;
	}
	free(shell->envtxt);
	shell->envtxt = genenv(shell->env);
}

char	*getsyspath(void)
{
	char	*buffer;
	char	*path;
	int		fd;
	int		first;
	char	*oldpath;

	buffer = NULL;
	first = 1;
	fd = open("/etc/paths", O_RDONLY);
	while (get_next_line(fd, &buffer))
	{
		if (!first)
		{
			oldpath = path;
			path = ft_strjoin(path, ":");
			free(oldpath);
			path = ft_strjoin(path, buffer);
		}
		else
			path = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
		first = 0;
	}
	return (path);
}

t_env	*environtoenv(char **environ, int i)
{
	t_env	*env;
	char	**mtab;

	mtab = ft_strsplit(environ[i], '=');
	if (ft_strequ(mtab[0], "SHLVL"))
	{
		mtab[1] = ft_itoa(ft_atoi(mtab[1]) + 1);
	}
	env = newenv(mtab[0], mtab[1]);
	free(mtab[0]);
	free(mtab[1]);
	free(mtab);
	return (env);
}

int		envlen(t_env *env)
{
	int nb;

	nb = 0;
	while (env)
	{
		nb++;
		env = env->next;
	}
	return (nb);
}
