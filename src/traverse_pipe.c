/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:18:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 15:18:25 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	traverse_pipe(t_exec *exec)
{
	int	i;

	if (pipe(exec->pipes + exec->pipe_i) < 0)
		return (-4);
	i = exec->pipe_i;
	exec->current_node = exec->current_node->left;
	exec->current_node->out_pipe = exec->pipes[i + 1];
	if (exec->current_node->here_doc && exec_heredoc(exec) < 0)
		return (-5);
	exec_leaf(exec);
	exec->current_node = exec->current_node->parent->right;
	if (exec->current_node->type == E_COMMAND)
	{
		exec->current_node->in_pipe = exec->pipes[i];
		if (exec->current_node->here_doc && exec_heredoc(exec) < 0)
			return (-5);
		exec_leaf(exec);
		wait (NULL);
		return (0);
	}
	else
	{
		exec->current_node->left->in_pipe = exec->pipes[i];
		traverse_pipe(exec);
	}
	wait (NULL);
	return (0);
}