/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:48:27 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/28 11:38:38 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/***************************************************************************
 * Execute a single command piping heredoc if needed
 * @param exec exec struct containing the command to execute
 * @return status of the command
 **************************************************************************/

static int	single_cmd_norme(t_exec *exec, int *status, int	*flag)
{
	if (exec->root->here_doc_list)
	{
		*status = exec_heredoc(exec);
		if (*status < 0)
		{
			*flag = 1;
			return (*status);
		}
		exec->root->in_pipe = exec->pipes;
		exec_leaf(exec);
		close(exec->pipes[0]);
	}
	else
	{
		*flag = 1;
		return (-9);
	}
	*flag = 0;
	return (0);
}

int	single_cmd(t_exec *exec)
{
	t_single_cmd	vars;

	if (exec->root->here_doc == 1 && check_heredoc_last_in(exec->current_node))
	{
		vars.tmp = single_cmd_norme(exec, &vars.status, &vars.flag);
		if (vars.flag)
			return (vars.tmp);
	}
	else if (check_builtins(exec->current_node->token_node->value)
		&& exec->current_node->left)
		vars.status = exec_leaf(exec);
	else
		vars.status = exec_scmd(exec);
	if (check_builtins(exec->current_node->token_node->value)
		&& !exec->current_node->left)
		return (vars.status);
	if (vars.status < 0 || vars.status == 1)
		return (vars.status);
	waitpid(-1, &vars.status, 0);
	waitpid(-1, &vars.status, 0);
	if (g_exit_status != 0)
		return (g_exit_status);
	if (WIFEXITED(vars.status))
		return (WEXITSTATUS(vars.status));
	return (0);
}
