/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:45:39 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/11 18:48:26 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_node_init(t_token *token, t_token_type token_type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (NULL);
	if (token_type == E_PIPE)
		new_node->parent = NULL;
	new_node->token_node = token;
	new_node->type = token_type;
	new_node->right = NULL;
	if (token_type != E_PIPE)
		new_node->left = NULL;
	new_node->here_doc = -1;
	new_node->here_doc_list = NULL;
	new_node->forked = 0;
	if (token_type == E_COMMAND || token_type == E_PIPE)
	{
		new_node->in_pipe = -1;
		new_node->out_pipe = -1;
	}
	return (new_node);
}