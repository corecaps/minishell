/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:09:01 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/28 10:30:02 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/stat.h>

void	find_binary_error(int code, char *name, t_exec *exec)
{
	if (code == 1)
		write(2, "minishell: permission denied \n", 29);
	else if (code == 2)
		write(2, "minishell: command not found \n", 29);
	ft_putstr_fd(name, 2);
	write(2, "\n", 1);
	close_pipes(exec);
	gc_env_free();
	gc_free();
	if (code == 1)
		exit (126);
	else
		exit (127);
}

/******************************************************************************
 * Find the binary in the path
 * @return the full path of the binary
 * @param name null terminated string of the name of the command
 *****************************************************************************/

char	*find_binary(char *name, t_exec *exec)
{
	char		*final_path;
	char		**path;

	final_path = check_absolute_relative_path(name);
	gc_add(final_path);
	if (final_path && access(final_path, X_OK) != -1)
		return (final_path);
	else if (final_path && access(final_path, X_OK) == -1)
		find_binary_error(1, name, exec);
	path = get_path();
	final_path = get_full_path(name, path);
	if (!final_path)
		find_binary_error(2, name, exec);
	else
		gc_add(final_path);
	if (final_path && access(final_path, X_OK) != -1)
		return (final_path);
	else if (final_path && access(final_path, X_OK) == -1)
		find_binary_error(1, name, exec);
	else
	{
		gc_add(final_path);
		exit(1);
	}
	return (NULL);
}
