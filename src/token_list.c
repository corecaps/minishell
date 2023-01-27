/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:50:43 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 14:49:58 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_bottom(t_token *head, t_token *new_node)
{
	t_token	*tmp;

	tmp = head;
	while (head && head->next_token)
		head = head->next_token;
	head->next_token = new_node;
	head = tmp;
}

void	add_token(t_data *data, t_token_type type, char *value)
{
	t_token	*new_node;

	new_node = (t_token *)gc_alloc(1,sizeof(t_token));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->next_token = NULL;
	if (type < E_WORD || type > E_END_OF_TOKEN)
		exit(EXIT_FAILURE);
	new_node->token_type = type;
	if (value == NULL)
		exit(EXIT_FAILURE);
	new_node->value = value;
	if (!data->start_token)
		data->start_token = new_node;
	else
		get_bottom(data->start_token, new_node);
}
