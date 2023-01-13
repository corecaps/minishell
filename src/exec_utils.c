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
	printf("[%d] redirecting %d to %d closing %d\n", getpid(), fd1, fd2, fd1);
	dup2(fd1, fd2);
	close(fd1);
}