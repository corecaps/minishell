/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:17:12 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/18 17:17:17 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int create_redir_node(t_ast_builder *ast_builder, t_token *token)
{
	t_ast *new_node;
	t_ast *tmp;

	new_node = malloc(sizeof (t_ast));
	if (new_node == NULL)
		return (-1);
	new_node->token_node = token;
	new_node->type = E_REDIRECTION;
	new_node->right = NULL;
	new_node->left = NULL;
	if (ast_builder->root == NULL)
	{
		new_node->parent = NULL;
		ast_builder->root = new_node;
		ast_builder->current = new_node;
	}
	else if ((ast_builder->current->type == E_REDIRECTION)
		|| (ast_builder->current->type == E_COMMAND ))
	{
		tmp = ast_builder->current;
		while (tmp->left)
			tmp = tmp->left;
		new_node->parent =tmp;
		tmp->left = new_node;
	}
	else
		return (-2);
	return (1);
}

int create_cmd_node(t_ast_builder *ast_builder,t_token *token)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (new_node == NULL)
		return (-1);
	new_node->token_node = token;
	new_node->type = E_COMMAND;
	new_node->left = NULL;
	new_node->right = NULL;
	if (ast_builder->root == NULL)
	{
		new_node->parent = NULL;
		ast_builder->root = new_node;
		ast_builder->current = new_node;
	}
	else if (ast_builder->current->type == E_REDIRECTION)
	{
		new_node->left = ast_builder->current;
		new_node->left->parent = new_node;
		ast_builder->root = new_node;
		ast_builder->current = new_node;
	}
	else if (ast_builder->current->type == E_COMMAND_ARG)
	{
		new_node->right = ast_builder->current;
		new_node->right->parent = new_node;
		ast_builder->root = new_node;
		ast_builder->current = new_node;
	}
	else if (ast_builder->current->type == E_COMMAND
		&& ast_builder->current->parent->type == E_PIPE
		&& ast_builder->current->parent->right == NULL)
	{
		new_node->parent = ast_builder->current->parent;
		ast_builder->current->parent->right = new_node;
		ast_builder->current = new_node;
	}
	else
		return (-2);
	return (1);
}

int create_pipe_node(t_ast_builder *ast_builder,t_token *token)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (new_node == NULL)
		return (-1);
	new_node->parent = NULL;
	new_node->type = E_PIPE;
	new_node->token_node = token;
	new_node->right = NULL;
	if (ast_builder->current->type == E_COMMAND
		&& ast_builder->current->parent == NULL)
	{
		new_node->left = ast_builder->current;
		ast_builder->root = new_node;
		new_node->left->parent = new_node;
	}
	else if (ast_builder->current->type == E_COMMAND
		&& ast_builder->current->parent->type == E_PIPE)
	{
		ast_builder->current->parent->right = new_node;
		new_node->parent = ast_builder->current->parent;
		new_node->left = ast_builder->current;
		new_node->left->parent = new_node;
	}
	else
		return (-2);
	return (1);
}

int create_cmd_arg_node(t_ast_builder *ast_builder,t_token *token)
{
	t_ast *new_node;
	t_ast *tmp;

	new_node = malloc(sizeof(t_ast));
	if (new_node == NULL)
		return (-1);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->type = E_COMMAND_ARG;
	new_node->token_node = token;
	if (ast_builder->current->type == E_COMMAND
		&& ast_builder->current->right == NULL)
	{
		new_node->parent = ast_builder->current;
		ast_builder->current->right = new_node;
	}
	else if (ast_builder->current->type == E_COMMAND
		&& ast_builder->current->right != NULL)
	{
		tmp = ast_builder->current->right;
		while (tmp->left)
			tmp = tmp->left;
		new_node->parent = tmp;
		tmp->left = new_node;
	}
	else
		return (-2);
	return (1);
}