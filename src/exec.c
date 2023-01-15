/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:09:16 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/12 17:47:01 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*****************************************************************************
 * Check if the node has redirections child nodes and apply them in left to
 * right order
 * @param node an E_COMMAND node
 * @return 0 in case of success, -2 in case of file error
 *****************************************************************************/
//TODO: extract methods from this function

int	apply_redirections(t_ast *node)
{
	int		fd;
	t_ast	*cursor;

	if (node->type == E_REDIRECTION)
	{
		if (ft_strncmp(node->token_node->value, ">>",2) == 0)
		{
			fd = open(node->token_node->next_token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (-2);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(node->token_node->value, "<<",2) == 0)
		{
			cursor = node;
			while (cursor->parent && cursor->type != E_COMMAND)
				cursor = cursor->parent;
			cursor->here_doc = 1;
		}
		else if (ft_strncmp(node->token_node->value, "<",1) == 0)
		{
			fd = open(node->token_node->next_token->value, O_RDONLY);
			if (fd == -1)
				return (-2);
			else
			{
				dup2(fd,STDIN_FILENO);
				close(fd);
			}
		}
		else if (ft_strncmp(node->token_node->value, ">",1) == 0)
		{
			fd = open(node->token_node->next_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-2);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
	}
	if (node->left)
		if (apply_redirections(node->left) < 0)
			return (-2);
	if (node->right)
		if (apply_redirections(node->right) < 0)
			return (-2);
	return (0);
}

int	check_heredoc_last_in(t_ast *current_node)
{
	t_ast *cursor;

	cursor = current_node;
	while (cursor && ft_strncmp(cursor->token_node->value, "<<", 3) != 0)
	{
		cursor = cursor->left;
	}
	if (cursor && !(cursor->left))
		return (1);
	while (cursor)
	{
		if ((ft_strncmp(cursor->token_node->value, "<", 2) == 0)
			|| (ft_strncmp(cursor->token_node->value, "<<", 3) == 0))
			return (1);
		cursor = cursor->left;
	}
	return (0);
}