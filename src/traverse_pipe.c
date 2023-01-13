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
	int	status;
	int pid,pid2;

	pid2 = -1;
	if (exec->current_node->type != E_PIPE)
		return (-10);
	if (pipe(exec->pipes + exec->pipe_i) < 0)
		return (-4);
	i = exec->pipe_i;
	exec->pipe_i += 2;
	exec->current_node = exec->current_node->left;
	exec->current_node->out_pipe = exec->pipes[i + 1];
	if (exec->current_node->here_doc > 0 && exec_heredoc(exec) < 0)
		return (-5);
	pid = exec_leaf(exec, exec->pipes[i]);
//	close(exec->pipes[i]);
	exec->current_node = exec->current_node->parent->right;
	if (exec->current_node->type == E_COMMAND)
	{
		exec->current_node->in_pipe = exec->pipes[i];
		if (exec->current_node->here_doc > 0 && exec_heredoc(exec) < 0)
		{
			return (-5);
		}
		pid2 = exec_leaf(exec, exec->pipes[i + 1]);
		close (exec->pipes[i]);
		close(exec->pipes[i + 1]);
//		return (0);
	}
	else
	{
		exec->current_node->left->in_pipe = exec->pipes[i];
		close(exec->pipes[i]);
		close(exec->pipes[i + 1]);
		status = traverse_pipe(exec);
//		waitpid(-1, &status, 0);
//		wait (NULL);
	}
	printf("[%d] end of traverse_pipe\n", getpid());
	printf("[%d] (2) waitpid [[%d]]\n", getpid(), pid2);
	if (pid2 > -1)
		waitpid(pid2, &status, 0);
	printf("[%d] (1) waitpid [[%d]]\n", getpid(), pid);
	waitpid(pid, &status, 0);
	return (status);

	wait (NULL);
	return (0);
}