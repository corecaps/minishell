/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:09:01 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/12 12:04:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/stat.h>

/******************************************************************************
 * Find the binary in the path
 * @return the full path of the binary
 * @param name null terminated string of the name of the command
 *****************************************************************************/

char	*find_binary(char *name)
{
	char		*final_path;
	char		**path;

	final_path = check_absolute_relative_path(name);
	gc_add(final_path);
	if (final_path && access(final_path, X_OK)  != -1)
		return (final_path);
	else if (final_path && access(final_path,X_OK) == -1)
	{
		write(2,"minishell: permission denied \n", 29);
		ft_putstr_fd(name, 2);
		write(2,"\n", 1);
		gc_env_free();
		gc_free();
		exit(126);
	}
	path = get_path();
	final_path = get_full_path(name, path);
	if (!final_path)
	{
		write(2,"minishell: command not found \n", 29);
		ft_putstr_fd(name, 2);
		write(2,"\n", 1);
		gc_env_free();
		gc_free();
		exit(127);
	}
	else
		gc_add(final_path);
	if (final_path && access(final_path, X_OK)  != -1)
		return (final_path);
	else if (final_path && access(final_path, X_OK)  == -1)
	{
		write(2,"minishell: permission denied \n", 29);
		ft_putstr_fd(name, 2);
		write(2,"\n", 1);
		gc_env_free();
		gc_free();
		exit(126);
	}
	else
	{
		gc_add(final_path);
		exit(1);
	}
}