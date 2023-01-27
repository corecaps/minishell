/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:05:06 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/26 10:05:20 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	***gc_env_alloc(int size)
{
	static char **env = NULL;

	if (size < 0 && env)
	{
		return (&env);
	}
	else if (size < 0 && !env)
		return (NULL);
	else if (size == 0)
		gc_env_free();
	else if (size > 0)
	{
		env = (char **) ft_calloc(size+1,sizeof(char *));
		if (!env)
			env = NULL;
	}
	gc_env_add(env);
	return (&env);
}

t_garbage	**gc_env_add(void *ptr)
{
	static t_garbage	*garbage = NULL;
	t_garbage			*new;

	if (ptr == NULL)
		return (&garbage);
	if (garbage && gc_check_double(garbage, ptr))
		return (&garbage);
	new = (t_garbage *)malloc(sizeof(t_garbage));
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

int	gc_env_del(void *ptr)
{
	t_garbage	*cursor;
	t_garbage	**gc;
	t_garbage	*prev;

	gc =  gc_env_add(NULL);
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

void	gc_env_free(void)
{
	t_garbage	*tmp;
	t_garbage	**garbage;
	t_garbage	*cursor;

	garbage = gc_env_add(NULL);
	if (!(*garbage))
		return ;
	cursor = (*garbage);
	while (cursor)
	{
		tmp = cursor;
		cursor = cursor->next;
		free(tmp->ptr);
		free(tmp);
	}
	(*garbage) = NULL;
}