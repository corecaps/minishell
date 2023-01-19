/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:51:44 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/13 14:51:55 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	apply_dup(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int		open_redir(char *path,int oflags, t_ast * node,int dest)
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