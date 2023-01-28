/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:48:27 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 14:50:45 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/***************************************************************************
 * Execute a single command piping heredoc if needed
 * @param exec exec struct containing the command to execute
 * @return status of the command
 **************************************************************************/

int	single_cmd(t_exec *exec, char ***env)
{
	int	status;

	(void)env;
	if (exec->root->here_doc == 1 && check_heredoc_last_in(exec->current_node))
	{
		if (exec->root->here_doc_list)
		{
			status = exec_heredoc(exec);
			if (status < 0)
				return (status);
			exec->root->in_pipe = exec->pipes;
			exec_leaf(exec);
			close(exec->pipes[0]);
		}
		else
			return (-9);
	}
	else if (check_builtins(exec->current_node->token_node->value)
		&& exec->current_node->left)
		status = exec_leaf(exec);
	else
		status = exec_scmd(exec);
	if (check_builtins(exec->current_node->token_node->value)
		&& !exec->current_node->left)
		return (status);
	if (status < 0 || status == 1)
	{
		return (status);
	}
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	if (g_exit_status != 0)
		return (g_exit_status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
