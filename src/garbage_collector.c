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

/******************************************************************************
 * Check if a pointer is already in the garbage collector
 * @param gc Pointer to the garbage collector
 * @param ptr Pointer to check
 * @return 1 if the pointer is already in the garbage collector, 0 otherwise
 *****************************************************************************/

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

void gc_free()
{
	t_garbage	*tmp;
	t_garbage	**garbage;


	garbage = gc_add(NULL);
	if (!(*garbage))
		printf("garbage collector is empty\n");
	while ((*garbage))
	{
		tmp = (*garbage);
		(*garbage) = (*garbage)->next;
		free(tmp->ptr);
		if (tmp)
			free(tmp);
	}
	(*garbage) = NULL;
}

/***************************************************************************
 * Add a pointer to the garbage collector
 * @param ptr Pointer to add
 * @return Pointer to the garbage collector
 ****************************************************************************/

t_garbage	**gc_add(void *ptr)
{
	static t_garbage	*garbage = NULL;
	t_garbage			*new;

	if (ptr == NULL)
		return (&garbage);
	if (garbage && gc_check_double(garbage, ptr))
		return (&garbage);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	if (garbage)
		new->next = garbage;
	else
		new->next = NULL;
	garbage = new;
	return (&garbage);
}

/******************************************************************************
 * Free a specific pointer in the garbage collector and remove it from
 * the garbage collector
 * @param ptr Pointer to remove
 * @return 1 if the pointer was removed, 0 otherwise
 *****************************************************************************/

int gc_remove(void *ptr)
{
	t_garbage	*cursor;
	t_garbage	**gc;
	t_garbage	*prev;

	gc = gc_add(NULL);
	cursor = *gc;
	if (!cursor)
		return (0);
	prev = NULL;
	while (cursor)
	{
		if (cursor->ptr == ptr)
		{
			if (prev)
				prev->next = cursor->next;
			else
				(*gc) = cursor->next;
			free(cursor->ptr);
			free(cursor);
			return (1);
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return (0);
}

/******************************************************************************
 * Allocate memory and add the pointer to the garbage collector
 * @param nmemb Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated memory or NULL if an error occured
 *****************************************************************************/

void	*gc_alloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	gc_add(ptr);
	return (ptr);
}