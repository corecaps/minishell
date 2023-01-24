/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:05:30 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:36:27 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*push(t_token_type type, t_stack *head)
{
	t_stack	*new_node;

	new_node = gc_alloc(1,sizeof(t_stack));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	if (head)
		new_node->next = head;
	else
		new_node->next = NULL;
	return (new_node);
}

t_token_type	pop(t_stack **head)
{
	t_token_type	result;
	t_stack			*tmp;

	if ((*head) == NULL)
		return (E_END_OF_TOKEN);
	tmp = (*head)->next;
	result = (*head)->type;
	gc_remove((*head));
	*head = tmp;
	return (result);
}

int	count_stack(t_stack *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i ++;
		head = head->next;
	}
	return (i);
}