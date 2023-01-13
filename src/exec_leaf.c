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
	if (builtin)
		return (run_builtin(exec, builtin));
	printf("[%d] forking\n", getpid());
	status = fork();
	if (status < 0)
		return (-5);
	if (status == 0)
	{
		run_leaf(exec, to_close);
		exit(0);
	}
//	printf("[%d] waiting for child %d\n", getpid(), status);
//	waitpid(status, NULL, 0);
	exec->n_child ++;
	return (status);
}