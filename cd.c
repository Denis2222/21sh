/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 14:47:33 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/26 17:47:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <dirent.h>
#include <sys/stat.h>

static int	isdir(char *path)
{
	struct stat	filestat;

	stat(path, &filestat);
	if ((filestat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	else
		return (0);
}

int			cdcmd(t_shell *shell, char **cmds)
{
	if (ft_tablen(cmds) > 2)
	{
		ft_printf("cd: Too many arguments\n");
		return (1);
	}
	if (cmds[1])
		changedir(shell, cmds[1]);
	else
		changedir(shell, envgetkey(shell->env, "HOME"));
	return (1);
}

void		changedir(t_shell *shell, char *path)
{
	DIR		*directory;
	char	*newpwd;

	if (access(path, F_OK) == 0)
	{
		if (isdir(path))
		{
			directory = opendir(path);
			if (directory)
			{
				chdir(path);
				envsetkey(shell->env, "OLDPWD", envgetkey(shell->env, "PWD"));
				newpwd = getdir();
				envsetkey(shell->env, "PWD", newpwd);
				closedir(directory);
				ft_strdel(&newpwd);
			}
			else
				ft_printf("Permission denied\n");
		}
		else
			ft_printf("Not a directory\n");
	}
	else
		ft_printf("Not file or directory\n");
}
