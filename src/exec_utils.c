/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:51:44 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/23 10:17:56 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*****************************************************************************
 * Apply dup2 and close to the file descriptor
 ****************************************************************************/

void	apply_dup(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

/*****************************************************************************
 * Open a file descriptor for the targeted file in redirection node
 * and apply dup2 then close to the file descriptor
 ****************************************************************************/

int	open_redir(char *path, int oflags, t_ast *node, int dest)
{
	int		fd;
	t_ast	*cursor;

	if (!path)
	{
		cursor = node;
		while (cursor->parent && cursor->type != E_COMMAND)
			cursor = cursor->parent;
		cursor->here_doc = 1;
		return (0);
	}
	fd = open(path, oflags, 0644);
	if (fd == -1)
		return (-2);
	apply_dup(fd, dest);
	return (0);
}
