/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:51 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 14:34:07 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**************************************************************************
 * Execute a leaf of the tree
 * @param exec exec struct containing the command to execute
 * @return status of the command
 **************************************************************************/

int exec_leaf(t_exec *exec, int to_close)
{
	t_f_builtin	builtin;
	int			status;

	builtin = check_builtins(exec->current_node->token_node->value);

	status = fork();
	if (status < 0)
		return (-5);
	if (status == 0)
	{
		if (builtin)
			run_builtin(exec, builtin);
		else
			run_leaf(exec, to_close);
		exit(0);
	}
	exec->n_child ++;
	return (status);
}