/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:13:41 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/08 15:13:59 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
 * Free all pointers in the garbage collector
 * @param garbage Pointer to the garbage collector
 *****************************************************************************/

void	garbage_collector_free(t_garbage *garbage)
{
	t_garbage *tmp;

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

t_garbage *garbage_collector_add(void *ptr)
{
	static t_garbage *garbage = NULL;
	t_garbage *new;
	t_garbage *bottom;

	if (ptr == NULL)
		return (garbage);
	if (!(new = malloc(sizeof(t_garbage))))
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
	return garbage;
}