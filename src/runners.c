/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:48:10 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 14:48:27 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	run_builtin(t_exec *exec, t_f_builtin builtin)
{
	if (exec->current_node->in_pipe > -1)
		apply_dup(exec->current_node->in_pipe, STDIN_FILENO);
	if (exec->current_node->out_pipe > -1)
		apply_dup(exec->current_node->out_pipe, STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (-2);
	builtin(get_args(exec->current_node), exec->envp);
	return (0);
}

int	run_leaf(t_exec *exec)
{
	char	**argv;
	char	*full_path;

	argv = get_args(exec->current_node);
	full_path = find_binary(exec->current_node->token_node->value);
	if (!full_path)
		return (-3);
	if (exec->current_node->in_pipe > -1)
		apply_dup(exec->current_node->in_pipe, STDIN_FILENO);
	if (exec->current_node->out_pipe > -1)
		apply_dup(exec->current_node->out_pipe, STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (-2);
	if (execve(full_path, argv, *exec->envp) < 0)
		exit (-6);
}