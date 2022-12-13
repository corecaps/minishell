/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:05:30 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/10 13:08:10 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*push(t_token_type type, t_stack *head)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
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
	free ((*head));
	*head = tmp;
	return (result);
}

t_token_type	peek(t_stack *head)
{
	return (head->type);
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

void	del_stack(t_stack *head)
{
	t_stack	*prev;

	if (!head)
		return ;
	prev = head;
	while (head && head->next)
	{
		head = head->next;
		free(prev);
		prev = head;
	}
	free(head);
}
