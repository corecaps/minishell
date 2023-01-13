/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:10:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 14:10:26 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**************************************************************************
 * Output the heredoc to the pipe
 * SHOULD BE EXECUTED IN CHILD PROCESS
 * @param exec
 *************************************************************************/

static void	here_doc_child(t_exec *exec)
{
	t_here_doc	*cursor;

	printf("[%d] closing %d dup2 %d to %d\n", getpid(), exec->pipes[exec->pipe_i], exec->pipes[exec->pipe_i+1], STDOUT_FILENO);
	close(exec->pipes[exec->pipe_i]);
	dup2(exec->pipes[exec->pipe_i + 1], STDOUT_FILENO);
	cursor = exec->current_node->here_doc_list;
	while (cursor && cursor->line)
	{
		write(exec->pipes[exec->pipe_i + 1], cursor->line, ft_strlen(cursor->line));
		write(exec->pipes[exec->pipe_i + 1], "\n", 1);
		cursor = cursor->next;
	}
	printf("[%d] closing %d\n", getpid(), exec->pipes[exec->pipe_i + 1]);
	close(exec->pipes[exec->pipe_i + 1]);
	exit(0);
}

/****************************************************************************
 * create a pipe and fork a process to write the heredoc to the pipe
 * SHOULD NOT BE IN CHILD PROCESS
 * @param exec exec struct
 * @return 0 if success, -4 if pipe failed, -5 if fork failed
 ***************************************************************************/

int	exec_heredoc(t_exec *exec)
{
	int	status;

	if (pipe(exec->pipes + exec->pipe_i) == -1)
		return (-4);
	printf("[%d] fork\n", getpid());
	status = fork();
	if (status == -1)
	{
		return (-5);
	}
	if (status == 0)
	{
		here_doc_child(exec);
	}
	else
	{
		close(exec->pipes[exec->pipe_i + 1]);
		exec->pipe_i += 2;
	}
	return (status);
}