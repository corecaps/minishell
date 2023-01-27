/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:18:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 15:19:16 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	cmd_node(t_exec *exec, int pipe_local_idx, int *pid)
{
	exec->current_node->in_pipe = exec->pipes + pipe_local_idx;
	if (exec->current_node->here_doc > 0
		&& check_heredoc_last_in(exec->current_node)
		&& exec_heredoc(exec) < 0)
		return (-5);
	pid[1] = exec_leaf(exec);
	if (pid[1] < 0)
	{
		close(exec->pipes[pipe_local_idx]);
		return (2);
	}
	close(exec->pipes[pipe_local_idx + 1]);
	return (0);
}

int	end_pipes(const t_exec *exec, int pipe_local_idx, int status,
	const int *pid)
{
	int	*return_status;

	if (pid[1] > -1)
	{
		waitpid(pid[1], return_status, 0);
		waitpid(pid[0], NULL, 0);
		close(exec->pipes[pipe_local_idx]);
		close(exec->pipes[pipe_local_idx + 1]);
		return (WEXITSTATUS((*return_status)));
	}
	else
	{
		waitpid(pid[0], return_status, 0);
		close(exec->pipes[pipe_local_idx]);
		close(exec->pipes[pipe_local_idx + 1]);
		if (status > 0)
			return (status);
		return (WEXITSTATUS((*return_status)));
	}
}

void	init_pipe(t_exec *exec, int *pipe_local_idx, int *status, int *pid2)
{
	(*pid2) = -1;
	(*status) = 0;
	(*pipe_local_idx) = exec->pipe_i;
	exec->pipe_i += 2;
	exec->current_node = exec->current_node->left;
	exec->current_node->out_pipe = exec->pipes + (*pipe_local_idx);
}

int	traverse_pipe(t_exec *exec)
{
	int	pipe_local_idx;
	int	status;
	int	pid[2];

	if (pipe(exec->pipes + exec->pipe_i) < 0)
		return (-4);
	init_pipe(exec, &pipe_local_idx, &status, &pid[1]);
	if (exec->current_node->here_doc > 0
		&& check_heredoc_last_in(exec->current_node) && exec_heredoc(exec) < 0)
		return (-5);
	pid[0] = exec_leaf(exec);
	close(exec->pipes[pipe_local_idx + 1]);
	exec->current_node = exec->current_node->parent->right;
	if (exec->current_node->type == E_COMMAND)
	{
		status = cmd_node(exec, pipe_local_idx, pid);
		if (status == 2 || status < 0)
			return (status);
	}
	else
	{
		exec->current_node->left->in_pipe = exec->pipes + pipe_local_idx;
		status = traverse_pipe(exec);
	}
	return (end_pipes(exec, pipe_local_idx, status, pid));
}
