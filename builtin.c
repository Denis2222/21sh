/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 22:05:31 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/26 17:41:47 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cmdstokeyvalue(char **cmds, char **key, char **value)
{
	char **tab;

	tab = NULL;
	if (ft_tablen(cmds) == 3)
	{
		*key = cmds[1];
		*value = cmds[2];
	}
	if (ft_tablen(cmds) == 2 && ft_strchr(cmds[1], '='))
	{
		tab = ft_strsplit(cmds[1], '=');
		if (ft_tablen(tab) == 2)
		{
			*key = tab[0];
			*value = tab[1];
		}
	}
}

int			setenvcmd(t_shell *shell, char **cmds)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	cmdstokeyvalue(cmds, &key, &value);
	if (key && value)
		if (ft_strlen(key) > 0 && ft_strlen(value) > 0)
			if (!ft_strchr(key, '=') && !ft_strchr(value, '='))
			{
				envsetkey(shell->env, key, value);
				shell_env_refresh(shell);
				return (1);
			}
	ft_printf("setenv: syntax error (setenv [KEY] [VALUE] |");
	ft_printf("setenv [KEY]=[VALUE])\n");
	return (0);
}

int			exitcmd(char **cmds)
{
	int	cmdlen;
	int	len;
	int	result;

	cmdlen = ft_tablen(cmds);
	if (cmdlen == 1)
		exit(EXIT_SUCCESS);
	else if (cmdlen == 2)
	{
		len = ft_strlen(cmds[1]);
		result = ft_atoi(cmds[1]);
		exit(result);
	}
	else
		ft_printf("exit: too many arguments\n");
	return (1);
}

int			builtin(t_shell *shell, char *cmd)
{
	char	**cmds;
	int		ret;

	ret = 0;
	cmds = ft_strsplit(cmd, ' ');
	if (ft_strequ(cmds[0], "cd"))
		ret = cdcmd(shell, cmds);
	if (ft_strequ(cmds[0], "exit"))
		ret = exitcmd(cmds);
	if (ft_strequ(cmds[0], "setenv"))
		ret = setenvcmd(shell, cmds);
	if (ft_strequ(cmds[0], "unsetenv"))
		ret = envdelkey(&shell->env, cmds[1]);
	if (ft_strequ(cmds[0], "env"))
		ret = listenv(shell->env);
	ft_tabfree(cmds);
	return (ret);
}
