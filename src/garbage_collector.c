/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:13:41 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:28:13 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gc_check_double(t_garbage *gc, void *ptr)
{
	t_garbage	*tmp;

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

	if (!garbage)
		printf("garbage collector is empty\n");
	while (garbage)
	{
		tmp = garbage;
		garbage = garbage->next;
		free(tmp->ptr);
		if (tmp)
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

	if (ptr == NULL)
		return (garbage);
	if (gc_check_double(garbage, ptr))
		return (garbage);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
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

t_garbage	**gc_remove(t_garbage **gc, void *ptr)
{
	t_garbage	*tmp;
	t_garbage	*prev;

	if (!gc || !ptr)
		return (NULL);
	tmp = *gc;
	prev = NULL;
	while (tmp)
	{
		if (tmp && tmp->ptr == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*gc = tmp->next;
			free(tmp);
			return (gc);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (gc);
}

void	*gc_alloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	garbage_collector_add(ptr);
	return (ptr);
}