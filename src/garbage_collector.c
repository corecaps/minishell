/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:13:41 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/12 13:06:44 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	gc_check_double(t_garbage *gc, void *ptr)
{
	t_garbage 	*tmp;

	tmp = gc;
	while (tmp)
	{
		if (tmp->ptr == ptr)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/******************************************************************************
 * Free all pointers in the garbage collector
 * @param garbage Pointer to the garbage collector
 *****************************************************************************/

void	garbage_collector_free(t_garbage *garbage)
{
	t_garbage	*tmp;

	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		free(tmp->ptr);
		free(tmp);
	}
}

/***************************************************************************
 * Add a pointer to the garbage collector
 * @param ptr Pointer to add
 * @return Pointer to the garbage collector
 ****************************************************************************/

t_garbage	*garbage_collector_add(void *ptr)
{
	static t_garbage	*garbage = NULL;
	t_garbage			*new;
	t_garbage			*bottom;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	if (ptr == NULL)
	{
		free(new);
		return (garbage);
	}
	if (gc_check_double(garbage, ptr))
	{
		free(new);
		return (garbage);
	}
	new->ptr = ptr;
	new->next = NULL;
	if (garbage)
	{
		bottom = garbage;
		while (bottom && bottom->next)
			bottom = bottom->next;
		bottom->next = new;
	}
	else
		garbage = new;
	return (garbage);
}
