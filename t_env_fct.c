/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 22:34:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/26 17:42:01 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*loadenv(char **environ)
{
	int		i;
	t_env	*new;
	t_env	*lst;
	t_env	*current;

	lst = NULL;
	i = -1;
	while (environ[++i])
	{
		new = environtoenv(environ, i);
		if (!lst)
		{
			lst = new;
			current = lst;
		}
		else
		{
			while (lst->next)
				lst = lst->next;
			lst->next = new;
		}
	}
	if (!environ[0])
		return (newenv("PATH", getsyspath()));
	return (current);
}

char	*envgetkey(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		else
			env = env->next;
	}
	if (ft_strequ(key, "HOME") ||
		ft_strequ(key, "PWD") ||
		ft_strequ(key, "OLDPWD") ||
		ft_strequ(key, "PATH"))
		return ("/");
	return (NULL);
}

int		envsetkey(t_env *env, char *key, char *value)
{
	int		keyfound;
	t_env	*init;

	init = env;
	keyfound = 0;
	while (env && !keyfound)
	{
		if (ft_strequ(env->key, key))
		{
			keyfound = 1;
			free(env->value);
			env->value = NULL;
			env->value = ft_strdup(value);
		}
		else
			env = env->next;
	}
	if (!keyfound)
		init = addenv(&init, newenv(key, value));
	return (1);
}

void	whileenvdelkey(t_env *env, t_env *last, t_env **list)
{
	t_env	*tmp;

	tmp = env;
	if (last)
	{
		last->next = env->next;
		delenv(tmp);
	}
	else
	{
		tmp = env;
		*list = env->next;
	}
}

int		envdelkey(t_env **list, char *key)
{
	int		keyfound;
	t_env	*env;
	t_env	*last;

	if (ft_strequ(key, "PATH"))
		return (envsetkey(*list, "PATH", getsyspath()));
	env = *list;
	last = NULL;
	keyfound = 0;
	while (env && !keyfound)
	{
		if (ft_strequ(env->key, key))
		{
			keyfound = 1;
			whileenvdelkey(env, last, list);
		}
		else
		{
			last = env;
			env = env->next;
		}
	}
	return (1);
}
