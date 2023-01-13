/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:42:26 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 13:42:31 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Count the number of pipes needed for the execution of the command
 * @param root root of the AST
 * @return number of pipes needed
 *****************************************************************************/

static int	count_pipes(t_ast *root)
{
	int	n_pipes;

	n_pipes = 0;
	if (root->here_doc_list)
		n_pipes++;
	if (root->type == E_PIPE)
	{
		n_pipes++;
		n_pipes += count_pipes(root->left);
		n_pipes += count_pipes(root->right);
	}
	return (n_pipes);
}

/*****************************************************************************
 * allocates memory for the pipes and the file descriptors
 * @param root root of the ast
 * @return an array of pipes, or NULL if an error occured
 ****************************************************************************/

static int	*init_pipes(t_ast *root)
{
	int	*pipefd;
	int	n_pipes;

	n_pipes = count_pipes(root);
	pipefd = malloc(sizeof(int) * n_pipes * 2);
	if (pipefd == NULL)
		return (NULL);
	return (pipefd);
}

/******************************************************************************
 * Initialize the data_struct for the execution off command line
 * @param current_node the current node of the AST
 * @param env environment variables
 * @return t_exec_data* the data struct, NULL if error
 *****************************************************************************/

static t_exec	*exec_init(t_ast *current_node, char ***env)
{
	t_exec	*new_exec;

	new_exec = malloc(sizeof(t_exec));
	if (new_exec == NULL)
		return (NULL);
	new_exec->current_node = current_node;
	new_exec->root = current_node;
	new_exec->envp = env;
	new_exec->pipes = init_pipes(current_node);
	if (new_exec->pipes == NULL)
		return (NULL);
	new_exec->pipe_i = 0;
	new_exec->n_child = 0;
	return (new_exec);
}

/******************************************************************************
 * Execute a command line traversing the AST
 * @param current_node starting point in the Abstract Syntax Tree
 * @param env current environment variables
 * @return -1 if an memory allocation error occurs,-2 if a open error occurs,
 * -3 if binary is not found, -4 if a pipe error occurs,
 * -5 if a fork error occurs, -6 if a exec error occurs,
 * -8 incorrect AST structure
 *****************************************************************************/

int	exec_cmd_line(t_ast *current_node, char ***env)
{
	t_exec	*exec;
	int		status;

	exec = exec_init(current_node, env);
	if (exec == NULL)
		return (-1);
	if (current_node->type == E_COMMAND)
		return (single_cmd(exec));
	else if (current_node->type == E_PIPE)
		status = traverse_pipe(exec);
	else
		return (-8);
	if (status < 0)
		return (status);
//	while (exec->n_child -- > 0)
//		wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}