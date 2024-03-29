/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:02:10 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 15:04:50 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * print error message to stderr in case of parser error
 ****************************************************************************/

void	parser_error(int *status)
{
	if (*status >= 0)
		return ;
	if (*status == -1)
		write(2, "Minishell error: malloc failed\n", 31);
	else if (*status == -2)
		write(2, "Minishell error: syntax error\n", 30);
	else if (*status == -3)
		write(2, "Minishell error: Out of bound token\n", 36);
	*status = 2;
}

/*****************************************************************************
 * print error message to stderr in case of exec error
 ****************************************************************************/

void	exec_error(int *status)
{
	if (*status >= 0)
		return ;
	if (*status == -1)
		write(2, "Minishell error: malloc failed\n", 31);
	else if (*status == -2)
		write(2, "Minishell error: open failed\n", 29);
	else if (*status == -3)
		write (2, "Minishell error: command not found\n", 35);
	else if (*status == -4)
		write(2, "Minishell error: pipe failed\n", 29);
	else if (*status == -5)
		write(2, "Minishell error: fork failed\n", 29);
	else if (*status == -6)
		write(2, "Minishell error: exec failed\n", 29);
	else if (*status == -9)
		write(2, "Minishell error: Empty Heredoc\n", 31);
	*status = 2;
}
