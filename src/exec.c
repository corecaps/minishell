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
 * execute the comnand in an E_COMMAND node applying redirections if needed
 * @param node an E_COMMAND node
 * @param env the environment
 * @return 0 if success, -1 if malloc error, -2 if open error,
 * -3 if binary not found, -4 if pipe error, -5 if fork error,
 * -6 if exec error, -7 if readline error (here_doc)
 *****************************************************************************/

int exec_command_node(t_ast *node, char **env)
{
	char	*full_path;
	char	**args;
	int		pid;
	int		pipe_fd[2];
	int		status;
	t_here_doc	*cursor;

	// printf("node->token_node->value: [%s]\n", node->token_node->value);
	full_path = find_binary(node->token_node->value);
	if (!full_path)
	{
		printf("HEllo\n");
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
	if (node->here_doc_list)
	{
		if (pipe(pipe_fd) == -1)
			return (-4);
		pid = fork();
		if (pid < 0)
			return (-5);
		if (pid == 0)
		{
			close(pipe_fd[0]);
			cursor = node->here_doc_list;
			while (cursor)
			{
				write(pipe_fd[1],cursor->line,ft_strlen(cursor->line));
				write(pipe_fd[1],"\n",1);
				//TODO free cursor->line and cursor
				cursor = cursor->next;
			}
			close(pipe_fd[1]);
		}
		else
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0],STDIN_FILENO);
			close(pipe_fd[0]);
			execve(full_path, args, env);
			waitpid(pid,NULL,0);
			return (0);
		}
	}
	execve(full_path, args, env);
	return (0);
}

/***************************************************************************
 * Use Readline to get the complete heredoc until the delimiter is entered
 * @param node The node containing the heredoc
 * @return 0 on success, -1 on malloc error, -7 on readline error
 **************************************************************************/

int parse_here_doc(t_ast *node)
{
	t_here_doc	*current_line;
	t_here_doc	*cursor;
	t_here_doc	*prev;
	t_ast		*cursor_node;

	cursor_node = node;
	node = node->left;
	while (node->type != E_REDIRECTION)
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
 * -7 if a readline error occurs
 *****************************************************************************/

int traverse_ast(t_ast *current_node, char **env)
{
	int	status;
	int	pipe_fd[2];
	int	pid;

	if (current_node->type == E_COMMAND)
		return (exec_command_node(current_node, env));
	else if (current_node->type == E_PIPE)
	{
		status = pipe(pipe_fd);
		if (status  < 0)
			return (-4);
		pid = fork();
		if (pid < 0)
			return (-5);
		else if (pid == 0)
		{
			close(pipe_fd[0]);
			current_node->left->out_pipe = pipe_fd[1];
			status = traverse_ast(current_node->left, env);
			if (status < 0)
				return (status);
			close (pipe_fd[1]);
		}
		else
		{

			close(pipe_fd[1]);
			if (current_node->right->type == E_COMMAND)
				current_node->right->in_pipe = pipe_fd[0];
			else
				current_node->right->left->in_pipe = pipe_fd[0];
			status = traverse_ast(current_node->right, env);
			if (status < 0)
				return (status);
			close(pipe_fd[0]);
			status = waitpid(pid,&status,0);
			if (status != 0)
				return (status);
		}
	}
	return (0);
}