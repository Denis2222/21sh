/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_chr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:53:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/26 18:22:52 by dmoureu-         ###   ########.fr       */
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
	{
		elem->next = elem;
		*list = elem;
	}
	else
	{
		while (current->next)
			current = current->next;
		elem->prev = current;
		current->next = elem;
	}
	return (*list);
}
