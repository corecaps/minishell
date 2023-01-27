/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:17:12 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/23 10:16:46 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*****************************************************************************
 * Create a redirection node and add it to the tree
 * if the current node is a here doc node, parse the here doc
 ****************************************************************************/

int	create_redir_node(t_data *data, t_token *token)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = ast_node_init(token, E_REDIRECTION);
	if (new_node == NULL)
		return (-1);
	if (data->root == NULL)
	{
		new_node->parent = NULL;
		data->root = new_node;
		data->current = new_node;
	}
	else if ((data->current->type == E_REDIRECTION)
		|| (data->current->type == E_COMMAND))
	{
		tmp = data->current;
		while (tmp->left)
			tmp = tmp->left;
		new_node->parent = tmp;
		tmp->left = new_node;
		if (ft_strncmp(token->value, "<<", 3) == 0)
			parse_here_doc(new_node);
	}
	return (1);
}

/*****************************************************************************
 * connect the new_node to the tree
 ****************************************************************************/

static void	ast_writing(t_data *data, t_ast *new_node)
{
	if (data->current->type == E_REDIRECTION)
	{
		new_node->left = data->current;
		new_node->left->parent = new_node;
		data->root = new_node;
		data->current = new_node;
	}
	else
	{
		new_node->right = data->current;
		new_node->right->parent = new_node;
		data->root = new_node;
		data->current = new_node;
	}
}

/*****************************************************************************
 * Create a command node and add it to the tree
 ****************************************************************************/

int	create_cmd_node(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_node_init(token, E_COMMAND);
	if (new_node == NULL)
		return (-1);
	if (data->root == NULL)
	{
		new_node->parent = NULL;
		data->root = new_node;
		data->current = new_node;
	}
	else if (data->current->type == E_REDIRECTION
		|| data->current->type == E_COMMAND_ARG)
		ast_writing(data, new_node);
	else if (data->current->type == E_COMMAND
		&& data->current->parent->type == E_PIPE
		&& data->current->parent->right == NULL)
	{
		new_node->parent = data->current->parent;
		data->current->parent->right = new_node;
		data->current = new_node;
	}
	else
		return (-2);
	return (1);
}

/*****************************************************************************
 * Create a pipe node and add it to the tree
 ****************************************************************************/

int	create_pipe_node(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_node_init(token, E_PIPE);
	if (new_node == NULL)
		return (-1);
	if (data->current->type == E_COMMAND
		&& data->current->parent == NULL)
	{
		new_node->left = data->current;
		data->root = new_node;
		new_node->left->parent = new_node;
	}
	else if (data->current->type == E_COMMAND
		&& data->current->parent->type == E_PIPE)
	{
		data->current->parent->right = new_node;
		new_node->parent = data->current->parent;
		new_node->left = data->current;
		new_node->left->parent = new_node;
	}
	else
		return (-2);
	return (1);
}

/*****************************************************************************
 * Create a command argument node and add it to the tree
 ****************************************************************************/

int	create_cmd_arg_node(t_data *data, t_token *token)
{
	t_ast	*new_node;
	t_ast	*tmp;

	new_node = ast_node_init(token, E_COMMAND_ARG);
	if (new_node == NULL)
		return (-1);
	if (data->current->type == E_COMMAND
		&& data->current->right == NULL)
	{
		new_node->parent = data->current;
		data->current->right = new_node;
	}
	else if (data->current->type == E_COMMAND
		&& data->current->right != NULL)
	{
		tmp = data->current->right;
		while (tmp->left)
			tmp = tmp->left;
		new_node->parent = tmp;
		tmp->left = new_node;
	}
	else
		return (-2);
	return (1);
}
