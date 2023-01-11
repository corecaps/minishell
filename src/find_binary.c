/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:09:01 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/09 18:09:31 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Find the binary in the path
 * @return the full path of the binary
 * @param name null terminated string of the name of the command
 *****************************************************************************/

char	*find_binary(char *name)
{
	char	*final_path;
	char	**path;

	final_path = check_absolute_relative_path(name);
	if (final_path)
		return (final_path);
	path = get_path();
	final_path = get_full_path(name, path);
	if (final_path && access(final_path, X_OK) != -1)
		return (final_path);
	else
		return (NULL);
}
