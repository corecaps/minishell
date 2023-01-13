/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:43:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 10:43:27 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/***************************************************************************
 * Prepare the writing part of the pipe and recursively call traverse_ast
 * @param current_node The current node
 * @param env The environment variables
 * @param pipe_fd The pipe file descriptors
 * @return 0 on success, -1 on malloc error, -2 if a open error occurs,
 * -3 if binary is not found, -4 if a pipe error occurs,
 * -5 if a fork error occurs, -6 if a exec error occurs,
 * -7 if a readline error occurs, -8 incorrect AST structure
 *****************************************************************************/

int write_pipe(t_ast *current_node, char ***env, const int *pipe_fd)
{
	int status;

	close(pipe_fd[0]);
	current_node->left->out_pipe = pipe_fd[1];
	status = exec_command_node(current_node->left, env);
	close(pipe_fd[1]);
	return (status);
}

/***************************************************************************
 * Prepare the writing part of the pipe and recursively call traverse_ast
 * @param current_node The current node
 * @param env The environment variables
 * @param pipe_fd The pipe file descriptors
 * @param pid The pid of the child process
 * @return 0 on success, -1 on malloc error, -2 if a open error occurs,
 * -3 if binary is not found, -4 if a pipe error occurs,
 * -5 if a fork error occurs, -6 if a exec error occurs,
 * -7 if a readline error occurs, -8 incorrect AST structure
 *****************************************************************************/

int read_pipe(t_ast *current_node, char ***env, const int *pipe_fd, int pid)
{
	int			status;
	int			pid2;
	t_f_builtin	builtin;

	pid2 = -1;
	close(pipe_fd[1]);
	if (current_node->right->type == E_COMMAND)
		current_node->right->in_pipe = pipe_fd[0];
	else
		current_node->right->left->in_pipe = pipe_fd[0];
	if (current_node->right->type == E_COMMAND)
	{
		builtin = check_builtins(current_node->token_node->value);
		if (!builtin)
		{
			pid2 = fork();
			if (pid2 < 0)
				return (-5);
			if (pid2 == 0)
			{
				status = exec_command_node(current_node->right, env);
				if (status < 0)
					return (status);
			}
		}
		else
		{
			status = exec_command_node(current_node->right, env);
			if (status < 0)
				return (status);
		}
	}
	else
	{
		status = exec_pipe(current_node->right, env);
		if (status < 0)
			return (status);
	}
	if (pid2 > 0)
	{
		close(pipe_fd[0]);
		waitpid(pid2, &status, 0);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[0]);
	return (status);
}

/******************************************************************************
 * execute an E_PIPE node
 * @param current_node The current node
 * @param env The environment variables
 * @return -1 if an memory allocation error occurs,-2 if a open error occurs,
 * -3 if binary is not found, -4 if a pipe error occurs,
 * -5 if a fork error occurs, -6 if a exec error occurs,
 * -7 if a readline error occurs, -8 incorrect AST structure
 *****************************************************************************/

int exec_pipe(t_ast *current_node, char ***env)
{
	int	status;
	int	pipe_fd[6];
	int	pid;

	// TODO Extract pipe
	status = pipe(pipe_fd);
	if (status < 0)
		return (-4);
	if (current_node->left->here_doc_list)
	{
		status = pipe(pipe_fd + 2);
		if (status < 0)
			return (-4);
	}
	if (current_node->right->type == E_COMMAND
		&& current_node->right->here_doc_list)
	{
		status = pipe(pipe_fd + 4);
		if (status < 0)
			return (-4);
	}
	pid = fork();
	if (pid < 0)
		return (-5);
	else if (pid == 0)
		exit(write_pipe(current_node, env, pipe_fd));
	else
		return read_pipe(current_node, env, pipe_fd, pid);
}