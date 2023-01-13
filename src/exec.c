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

/******************************************************************************
 * check if cmd is a builtin
 * @param cmd name of the command
 * @return pointer to the builtin function if found, else NULL
 *****************************************************************************/

int pipe_heredoc(t_ast *current_node, int pid2, int *pipe_fd);

int run(t_ast *current_node, char ***env, int *status, int pid2,
		const int *pipe_fd);

/******************************************************************************
 * execute the comnand in an E_COMMAND node applying redirections if needed
 * @param node an E_COMMAND node
 * @param env the environment
 * @return 0 if success, -1 if malloc error, -2 if open error,
 * -3 if binary not found, -4 if pipe error, -5 if fork error,
 * -6 if exec error, -7 if readline error (here_doc)
 *****************************************************************************/


int	exec_command_node(t_ast *node, char ***env)
{
	char	*full_path;
	char	**args;
	int		status;
	t_f_builtin builtin;

	builtin = check_builtins(node->token_node->value);
	if (!builtin)
	{
		full_path = find_binary(node->token_node->value);
		if (!full_path)
			return (-3);
	}
	args = get_args(node);
	if (node->in_pipe > -1)
	{
		dup2(node->in_pipe,STDIN_FILENO);
		close(node->in_pipe);
	}
	if (node->out_pipe > -1)
	{
		dup2(node->out_pipe,STDOUT_FILENO);
		close(node->out_pipe);
	}
	if (node->left)
	{
		status = apply_redirections(node->left);
		if (status < 0)
			return (status);
	}
	if (builtin)
		builtin(args, env);
	else
		execve(full_path, args, *env);
	return (0);
}


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


/******************************************************************************
 * Traverse the AST from current node and execute the commands
 * @param current_node starting point in the Abstract Syntax Tree
 * @param env current environment variables
 * @return -1 if an memory allocation error occurs,-2 if a open error occurs,
 * -3 if binary is not found, -4 if a pipe error occurs,
 * -5 if a fork error occurs, -6 if a exec error occurs,
 * -7 if a readline error occurs, -8 incorrect AST structure
 *****************************************************************************/

int traverse_ast(t_ast *current_node, char ***env)
{
	int			status;
	int			pid2;
	t_f_builtin	builtin;
	int			pipe_fd[2];

	if (current_node->type == E_COMMAND)
	{
		builtin = check_builtins(current_node->token_node->value); // TODO Store builtin f pointer in node
		if (current_node->here_doc_list) // TODO check if heredoc is the last input redirection
		{
			pid2 = pipe_heredoc(current_node, pid2, pipe_fd);
			if (pid2 < 0)
				return (pid2);
		}
		if (!builtin)
			return run(current_node, env, &status, pid2, pipe_fd);
		else
			return (exec_command_node(current_node, env));
	}
	else if (current_node->type == E_PIPE)
		return (exec_pipe(current_node, env));
	else
		return (-8);
}

int run(t_ast *current_node, char ***env, int *status, int pid2,
		const int *pipe_fd)
{
	int pid;

	pid = fork();
	if (pid < 0)
		return (-5);
	if (pid == 0)
	{
		if (current_node->here_doc_list && check_heredoc_last_in(current_node))
		{
			dup2(pipe_fd[0],STDIN_FILENO);
			close(pipe_fd[0]);
		}
		(*status) = exec_command_node(current_node, env);
		if ((*status) < 0)
			exit((*status));
	}
	waitpid(pid2, status, 0);
	waitpid(pid,status,0);
	if (WIFEXITED(*status))
		return (*status);
	return (0);
}

int pipe_heredoc(t_ast *current_node, int pid2, int *pipe_fd)
{
	t_here_doc *cursor;

	if (pipe(pipe_fd) == -1)
				return (-4);
	pid2 = fork();
	if (pid2 < 0)
				return (-5);
	if (pid2 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1],STDOUT_FILENO);
		cursor = current_node->here_doc_list;
		while (cursor && cursor->line)
		{
			write(pipe_fd[1],cursor->line,ft_strlen(cursor->line));
			write(pipe_fd[1],"\n",1);
			cursor = cursor->next;
		}
		close(pipe_fd[1]);
		exit (0);
	}
	else
	{
		close(pipe_fd[1]);
	}
	return pid2;
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