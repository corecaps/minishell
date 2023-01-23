/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:34:48 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/23 10:12:24 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "data_structures.h"

/*****************************************************************************
 *
 * Skip white space characters
 * 
 ****************************************************************************/

void	skip_whitespaces(t_data *data)
{
	while (data->line[data->end] == ' ' || data->line[data->end] == '\t'
		|| data->line[data->end] == '\n' || data->line[data->end] == '\v'
		|| data->line[data->end] == '\f' || data->line[data->end] == '\r')
		data->end++;
}

/*****************************************************************************
 *
 * Create token linked list from input line
 * 
 ****************************************************************************/

void	lexer(t_data *data, char ***env)
{
	data->end = 0;
	while (data->end < (int)ft_strlen(data->line))
	{
		skip_whitespaces(data);
		data->index = data->end;
		if (data->line[data->end] == '|')
			add_pipe_token(data);
		else if (data->line[data->end] == '>' || data->line[data->end] == '<')
			add_redirect_token(data);
		else if (data->line[data->end] == '\'' || data->line[data->end] == '\"')
			add_quoted_token(data, env);
		else if (data->line[data->end] > 32 && data->line[data->end] < 127)
			add_word_token(data, ' ', env);
		else
			break ;
	}
	add_token(data, E_END_OF_TOKEN, "");
}
