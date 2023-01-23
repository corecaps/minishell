/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:10 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/23 11:02:14 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_error(int status)
{
	if (status == -1)
		write(2,"Minishell error: malloc failed\n", 31);
	else if (status == -2)
		write(2,"Minishell error: syntax error\n", 30);
	else if (status == -3)
		write(2,"Minishell error: Out of bound token\n", 36);
}

void	exec_error(int status)
{
	if (status == -1)
		write(2,"Minishell error: malloc failed\n", 31);
	else if (status == -2)
		write(2,"Minishell error: open failed\n", 29);
	else if (status == -3)
		write (2,"Minishell error: command not found\n", 35);
	else if (status == -4)
		write(2,"Minishell error: pipe failed\n", 29);
	else if (status == -5)
		write(2,"Minishell error: fork failed\n", 29);
	else if (status == -6)
		write(2,"Minishell error: exec failed\n", 29);
}
