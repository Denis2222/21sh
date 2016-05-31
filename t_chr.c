/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_chr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:53:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/31 18:51:41 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_chr	*newtchar(char chr)
{
	t_chr	*c;

	c = (t_chr*)ft_memalloc(sizeof(t_chr));
	c->chr = chr;
	c->next = NULL;
	c->prev = NULL;
	return (c);
}

t_chr	*addtchar(t_chr **list, t_chr *elem)
{
	t_chr	*current;
	t_chr	*first;

	first = *list;
	current = *list;
	if (!*list)
		*list = elem;
	else
	{
		while (current->next)
			current = current->next;
		elem->prev = current;
		current->next = elem;
	}
	return (*list);
}

t_chr	*addtcharto(t_chr **list, t_chr *elem, int to)
{
	t_chr	*current;
	t_chr	*first;
	t_chr	*next;
	int		pos;

	pos = 0;
	first = *list;
	current = *list;
	while (current->next && pos != to)
	{
		pos++;
		current = current->next;
	}
	elem->prev = current;
	next = current->next;
	current->next = elem;
	elem->next = next;
	return (*list);
}

int		tcharlen(t_chr *list)
{
	t_chr	*current;
	int		len;

	len = 0;
	current = list;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	debugtchar(t_chr *line)
{
	t_chr	*current;

	current = line;
	ft_putchar_fd(1, '\n');
	while (current)
	{
		ft_putchar_fd(1, current->chr);
		current = current->next;
	}
	ft_putchar_fd(1, '\n');
}

void	printtchar(t_chr *line)
{
	t_chr	*current;

	current = line;
	while (current)
	{
		ft_putchar(current->chr);
		current = current->next;
	}
}

int		tcharlenfrom(t_chr *line, int i)
{
	t_chr	*current;
	int		pos;
	int		len;

	len = 0;
	pos = 0;
	current = line;
	while (current)
	{
		pos++;
		if (pos > i)
			len++;
		current = current->next;
	}
	return (len);
}

void	printtcharfrom(t_chr *line, int i)
{
	t_chr	*current;
	int		pos;

	pos = 0;
	current = line;
	while (current)
	{
		pos++;
		if (pos > i)
			ft_putchar(current->chr);
		current = current->next;
	}
}
