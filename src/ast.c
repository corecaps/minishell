/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:24:54 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/09 14:49:27 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*get_top(t_ast *node)
{
	while (node && node->parent)
		node = node->parent;
	return (node);
}

t_ast	*add_left(t_ast *parent, t_token *token)
{
	t_ast	*new_node;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (NULL);
	new_node->token_node = token;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->in_pipe = -1;
	new_node->out_pipe = -1;
	new_node->here_doc = -1;
	new_node->here_doc_list = NULL;
	new_node->parent = parent;
	if (parent)
		parent->left = new_node;
	return (new_node);
}

t_ast	*add_right(t_ast *parent, t_token *token)
{
	t_ast	*new_node;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (NULL);
	new_node->token_node = token;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->in_pipe = -1;
	new_node->out_pipe = -1;
	new_node->here_doc = -1;
	new_node->here_doc_list = NULL;
	new_node->parent = parent;
	if (parent)
		parent->right = new_node;
	return (new_node);
}

void	del_ast(t_ast *top)
{
	if (top == NULL)
		return ;
	del_ast(top->left);
	del_ast(top->right);
	free(top);
}