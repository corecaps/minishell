/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:48:10 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:34:00 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	run_builtin(t_exec *exec, t_f_builtin builtin)
{
	if (exec->current_node->in_pipe != NULL)
		apply_dup(exec->current_node->in_pipe[0], STDIN_FILENO);
	if (exec->current_node->out_pipe != NULL)
		apply_dup(exec->current_node->out_pipe[1], STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (2);
	builtin(get_args(exec->current_node), &exec->envp);
	return (0);
}

int	run_leaf(t_exec *exec)
{
	char	**argv;
	char	*full_path;

	if (exec->current_node->in_pipe != NULL)
		close(exec->current_node->in_pipe[1]);
	if (exec->current_node->out_pipe != NULL)
		close(exec->current_node->out_pipe[0]);
	argv = get_args(exec->current_node);
	full_path = find_binary(exec->current_node->token_node->value);
	if (!full_path)
		return (3);
	if (exec->current_node->in_pipe != NULL)
		apply_dup(exec->current_node->in_pipe[0], STDIN_FILENO);
	if (exec->current_node->out_pipe != NULL)
		apply_dup(exec->current_node->out_pipe[1], STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (2);
	execve(full_path, argv, exec->envp);
	exit (6);
}
