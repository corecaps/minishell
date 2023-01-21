/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:24:54 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:11:32 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
 * Get the top of the Abstract Syntax Tree
 * @param node any node of the Abstract Syntax Tree
 * @return the top of the Abstract Syntax Tree
 ****************************************************************************/

t_ast	*get_top(t_ast *node)
{
	while (node && node->parent)
		node = node->parent;
	return (node);
}

/*****************************************************************************
 * Add a child to node and set the parent of the child to node
 * @param parent the parent node
 * @param token the token to add to the node
 * @return the leftmost node of the Abstract Syntax Tree
 ****************************************************************************/

t_ast	*add_left(t_ast *parent, t_token *token)
{
	t_ast	*new_node;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (NULL);
	new_node->token_node = token;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->in_pipe = NULL;
	new_node->out_pipe = NULL;
	new_node->here_doc = -1;
	new_node->here_doc_list = NULL;
	new_node->parent = parent;
	if (parent)
		parent->left = new_node;
	return (new_node);
}

/*****************************************************************************
 * Add a child to node and set the parent of the child to node
 * @param parent the parent node
 * @param token the token to add to the node
 * @return the rightmost node of the Abstract Syntax Tree
 *****************************************************************************/

t_ast	*add_right(t_ast *parent, t_token *token)
{
	t_ast	*new_node;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (NULL);
	new_node->token_node = token;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->in_pipe = NULL;
	new_node->out_pipe = NULL;
	new_node->here_doc = -1;
	new_node->here_doc_list = NULL;
	new_node->parent = parent;
	if (parent)
		parent->right = new_node;
	return (new_node);
}

/*****************************************************************************
 * Free the entire Abstract Syntax Tree from memory
 * @param node The top of the Abstract Syntax Tree
 ****************************************************************************/

void	del_ast(t_ast *top)
{
	t_garbage	*garbage;

	if (top == NULL)
		return ;
	del_ast(top->left);
	del_ast(top->right);
	garbage = garbage_collector_add(NULL);
	gc_remove(&garbage, top);
	free(top);
}
