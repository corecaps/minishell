/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:18:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 15:11:14 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	traverse_pipe(t_exec *exec)
{
	int	pipe_local_idx;
	int	status;
	int	return_status;
	int	pid;
	int	pid2;

	pid2 = -1;
	status = 0;
	if (pipe(exec->pipes + exec->pipe_i) < 0)
		return (-4);
	pipe_local_idx = exec->pipe_i;
	exec->pipe_i += 2;
	exec->current_node = exec->current_node->left;
	exec->current_node->out_pipe = exec->pipes + pipe_local_idx;
	if (exec->current_node->here_doc > 0
		&& check_heredoc_last_in(exec->current_node) && exec_heredoc(exec) < 0)
		return (-5);
	pid = exec_leaf(exec);
	close(exec->pipes[pipe_local_idx + 1]);
	exec->current_node = exec->current_node->parent->right;
	if (exec->current_node->type == E_COMMAND)
	{
		exec->current_node->in_pipe = exec->pipes + pipe_local_idx;
		if (exec->current_node->here_doc > 0
			&& check_heredoc_last_in(exec->current_node) && exec_heredoc(exec) < 0)
			return (-5);
		pid2 = exec_leaf(exec);
		if (pid2 < 0)
		{
			close(exec->pipes[pipe_local_idx]);
			return (2);
		}
		close(exec->pipes[pipe_local_idx + 1]);
	}
	else
	{
		exec->current_node->left->in_pipe = exec->pipes + pipe_local_idx;
		status = traverse_pipe(exec);
	}
	if (pid2 > -1)
	{
		waitpid(pid2, &return_status, 0);
		waitpid(pid, NULL, 0);
		close(exec->pipes[pipe_local_idx]);
		close(exec->pipes[pipe_local_idx + 1]);
		return (WEXITSTATUS(return_status));
	}
	else
	{
		waitpid(pid, &return_status, 0);
		close(exec->pipes[pipe_local_idx]);
		close(exec->pipes[pipe_local_idx + 1]);
		if (status > 0)
			return (status);
		return (WEXITSTATUS(return_status));
	}
}
