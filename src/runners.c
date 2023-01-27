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
#include <sys/stat.h>

int is_dir(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}

int	run_builtin(t_exec *exec, t_f_builtin builtin)
{
	int	status;

	if (exec->current_node->in_pipe != NULL)
		apply_dup(exec->current_node->in_pipe[0], STDIN_FILENO);
	if (exec->current_node->out_pipe != NULL)
		apply_dup(exec->current_node->out_pipe[1], STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (-2);
	status = builtin(get_args(exec->current_node), exec->line);
	return (status);
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
		exit (126);
	if (is_dir(full_path))
	{
		write(2,"minishell: ", 11);
		ft_putstr_fd(full_path,2);
		write(2," is a directory\n", 16);
		gc_env_free();
		gc_free();
		exit (126);
	}
	if (exec->current_node->in_pipe != NULL)
		apply_dup(exec->current_node->in_pipe[0], STDIN_FILENO);
	if (exec->current_node->out_pipe != NULL)
		apply_dup(exec->current_node->out_pipe[1], STDOUT_FILENO);
	if (exec->current_node->left
		&& (apply_redirections(exec->current_node) < 0))
		return (-2);
	execve(full_path, argv, exec->envp);
	gc_env_free();
	gc_free();
	exit (1);
}