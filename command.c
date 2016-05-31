/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 22:05:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/31 15:12:37 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		command_try_paths(t_shell *shell, char **cmds)
{
	char	**paths;
	char	*prgtry;
	char	*tmpprgtry;
	int		i;
	int		result;

	result = 0;
	paths = ft_strsplit(envgetkey(shell->env, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmpprgtry = ft_strjoin(paths[i], "/");
		prgtry = ft_strjoin(tmpprgtry, cmds[0]);
		result = execve(prgtry, cmds, shell->envtxt);
		free(tmpprgtry);
		free(prgtry);
		i++;
	}
	ft_tabfree(paths);
	return (result);
}

int		command(t_shell *shell, char *cmd)
{
	int		result;
	char	**cmds;

	result = 0;
	cmds = ft_strsplit(cmd, ' ');
	if (ft_tablen(cmds) > 0)
	{
		if (envgetkey(shell->env, "PATH"))
		{
			result = command_try_paths(shell, cmds);
		}
		result = execve(cmds[0], cmds, shell->envtxt);
		if (ft_strcmp(cmd, "") != 0 || result != 0)
			ft_printf("{red}Command not found !{eoc}\n");
	}
	ft_tabfree(cmds);
	free(cmd);
	return (result);
}
