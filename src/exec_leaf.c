/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:51 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/23 10:17:54 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**************************************************************************
 * Execute a leaf of the tree
 * @param exec exec struct containing the command to execute
 * @return status of the command
 **************************************************************************/

int	exec_leaf(t_exec *exec)
{
	t_f_builtin	builtin;
	int			status;
	int			pid;

	builtin = check_builtins(exec->current_node->token_node->value);
	pid = fork();
	status = 0;
	if (pid < 0)
		return (-5);
	if (pid == 0)
	{
		reset_signals();
		if (builtin)
			status = run_builtin(exec, builtin);
		else
			status = run_leaf(exec);
		exit(status);
	}
	exec->n_child ++;
	return (pid);
}

/**************************************************************************
 * Execute a single command, do not fork if command is a builtin
 * @return status of the command
 **************************************************************************/

int	exec_scmd(t_exec *exec)
{
	t_f_builtin	builtin;
	int			status;

	builtin = check_builtins(exec->current_node->token_node->value);
	if (builtin)
		return (run_builtin(exec, builtin));
	status = fork();
	if (status < 0)
		return (-5);
	if (status == 0)
	{
		reset_signals();
		status = run_leaf(exec);
		exit(status);
	}
	exec->n_child ++;
	return (status);
}
