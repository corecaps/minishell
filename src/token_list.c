/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:50:43 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/12 14:47:31 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_bottom(t_token *head, t_token *new_node)
{
	t_token	*tmp;

	tmp = head;
	while (head && head->next_token)
		head = head->next_token;
	head->next_token = new_node;
	head = tmp;
}

// t_token	*add_token(t_token *head, t_token_type type, char *value)
// {
// 	t_token	*new_node;
// 	t_token	*bottom;

// 	if (value == NULL || type > E_DOULE_QUOTED || type < E_WORD)
// 		return (NULL);
// 	new_node = malloc(sizeof(t_token));
// 	if (new_node == NULL)
// 		return (NULL);
// 	new_node->next_token = NULL;
// 	new_node->token_type = type;
// 	new_node->value = value;
// 	if (head != NULL)
// 	{
// 		bottom = get_bottom(head);
// 		bottom->next_token = new_node;
// 		return (head);
// 	}
// 	return (new_node);
// }

void	add_token(t_data *data, t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->next_token = NULL;
	new_node->token_type = type;
	new_node->value = value;
	if (!data->start_token)
		data->start_token = new_node;
	else
		get_bottom(data->start_token, new_node);
}

int	count_token(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next_token;
		i ++;
	}
	return (i);
}

void	del_token_list(t_token *head)
{
	t_token	*prev;

	prev = head;
	while (head)
	{
		head = head->next_token;
		if (prev->value && prev->token_type == E_WORD)
			free(prev->value);
		if (prev)
			free(prev);
		prev = head;
	}
}
