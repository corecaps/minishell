/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:09:16 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/22 13:09:41 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * check if cmd is a builtin
 * @param cmd name of the command
 * @return pointer to the builtin function if found, else NULL
 *****************************************************************************/
// TODO : move in builtin.c
// TODO : code builtins functions

t_f_builtin check_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo",5) == 0)
		return (ft_echo);
	else if (ft_strncmp(cmd, "cd",3) == 0)
		return (ft_cd);
	else if (ft_strncmp(cmd, "pwd",4) == 0)
		return (ft_pwd);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (ft_export);
	// else if (ft_strncmp(cmd, "unset", 5) == 0)
	// 	return (ft_unset);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (ft_env);
	else if (ft_strncmp(cmd, "exit",5) == 0)
		return (ft_exit);
	return (NULL);
}
/******************************************************************************
 * execute the comnand in an E_COMMAND node applying redirections if needed
 * @param node an E_COMMAND node
 * @param env the environment
 * @return 0 if success, -1 if malloc error, -2 if open error,
 * -3 if binary not found, -4 if pipe error, -5 if fork error,
 * -6 if exec error, -7 if readline error (here_doc)
 *****************************************************************************/
// TODO : extract methods from this function
// TODO : Leak in here_doc
int	exec_command_node(t_ast *node, char ***env)
{
	char	*full_path;
	char	**args;
	int		pid;
	int		pid2;
	int		pipe_fd[2];
	int		status;
	t_f_builtin builtin;
	t_here_doc	*cursor;

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
		if (node->here_doc == 1)
			parse_here_doc(node);
	}
//	if (node->here_doc_list)
//	{
//		if (pipe(pipe_fd) == -1)
//			return (-4);
//		pid = fork();
//		if (pid < 0)
//			return (-5);
//		if (pid == 0)
//		{
//			close(pipe_fd[0]);
//			cursor = node->here_doc_list;
//			while (cursor)
//			{
//				write(pipe_fd[1],cursor->line,ft_strlen(cursor->line));
//				write(pipe_fd[1],"\n",1);
//				//TODO free cursor->line and cursor
//				cursor = cursor->next;
//			}
//			close(pipe_fd[1]);
//		}
//		else
//		{
//			close(pipe_fd[1]);
//			dup2(pipe_fd[0],STDIN_FILENO);
//			close(pipe_fd[0]);
//			if (builtin)
//			{
//				builtin(args, env);//env ** or ***
//			}
//			else
//			{
//				pid2 = fork();
//				if (pid2 < 0)
//					return (-5);
//				if (pid2 == 0)
//				{
//					execve(full_path, args, *env);
//				}
//				else
//				{
//					waitpid(pid2,&status,0);
//				}
//			}
//			waitpid(pid,NULL,0);
//			return (0);
//		}
//	}
	if (builtin)
	{
		builtin(args, env);
	}
	else
		execve(full_path, args, *env);
	return (0);
}

/***************************************************************************
 * Use Readline to get the complete heredoc until the delimiter is entered
 * @param node The node containing the heredoc
 * @return 0 on success, -1 on malloc error, -7 on readline error
 **************************************************************************/
// TODO : extract methods from this function
int	parse_here_doc(t_ast *node)
{
	t_here_doc	*current_line;
	t_here_doc	*cursor;
	t_here_doc	*prev;
	t_ast		*cursor_node;

	cursor_node = node;
	node = node->left;
	while (ft_strncmp(node->token_node->value,"<<",2) != 0)
	{
		node = node->left;
	}
	prev = NULL;
	while (1)
	{
		current_line = malloc(sizeof(t_here_doc));
		if (!current_line)
			return (-1);
		current_line->line = readline("heredoc> ");
		if (current_line->line == NULL)
			return (-7);
		current_line->next = NULL;
		if (cursor_node->here_doc_list == NULL)
			cursor_node->here_doc_list = current_line;
		else
		{
			cursor = cursor_node->here_doc_list;
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = current_line;
		}
		if (ft_strncmp(current_line->line,node->token_node->next_token->value,ft_strlen(node->token_node->next_token->value)) == 0)
		{
			if (prev)
				prev->next = NULL;
			else
				cursor_node->here_doc_list = NULL;
			free(current_line->line);
			free(current_line);
			break;
		}
		prev = current_line;
	}
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
			// TODO : correct flags for append mode
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
	current_node->left->forked =1;
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
	int status;
	int pid2;
	t_f_builtin builtin;

	pid2 = -1;
	close(pipe_fd[1]);
	if (current_node->right->type == E_COMMAND)
		current_node->right->in_pipe = pipe_fd[0];
	else
		current_node->right->left->in_pipe = pipe_fd[0];
	if (current_node->right->type == E_COMMAND)
	{
		// TODO : extract method (repeated from traverse_ast)
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
	status = waitpid(pid, &status, WUNTRACED);
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
	int status;
	int pipe_fd[2];
	int pid;

	status = pipe(pipe_fd);
	if (status < 0)
		return (-4);
	pid = fork();
	if (pid < 0)
		return (-5);
	else if (pid == 0)
	{
		write_pipe(current_node, env, pipe_fd);
		exit(0);
	}
	else
		return read_pipe(current_node, env, pipe_fd, pid);
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
	int status;
	int pid;
	t_f_builtin builtin;
	if (current_node->type == E_COMMAND)
	{
		builtin = check_builtins(current_node->token_node->value);
		if (!builtin)
		{
			pid = fork();
			if (pid < 0)
				return (-5);
			if (pid == 0)
				return (exec_command_node(current_node, env));
			else
				status = waitpid(pid, &status, 0);
			return (status);
		}
		else
			return (exec_command_node(current_node, env));
	}
	else if (current_node->type == E_PIPE)
		return (exec_pipe(current_node,env));
	else
		return (-8);
}