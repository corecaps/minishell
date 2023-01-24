/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:18:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:37:24 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	traverse_pipe(t_exec *exec)
{
	int	pipe_local_idx;
	int	status;
	int return_status;
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
	if (exec->current_node->here_doc > 0 && exec_heredoc(exec) < 0)
		return (-5);
	pid = exec_leaf(exec);
	close(exec->pipes[pipe_local_idx + 1]);
	exec->current_node = exec->current_node->parent->right;
	if (exec->current_node->type == E_COMMAND)
	{
		exec->current_node->in_pipe = exec->pipes + pipe_local_idx;
		if (exec->current_node->here_doc > 0 && exec_heredoc(exec) < 0)
			return (-5);
		pid2 = exec_leaf(exec);
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
		return (WEXITSTATUS(return_status));
	}
	else
	{
		waitpid(pid, &return_status, 0);
		if (status > 0)
			return (status);
		return (WEXITSTATUS(return_status));
	}
}