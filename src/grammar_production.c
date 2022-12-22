/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_production.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:24:12 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/22 11:51:41 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*******************************************************************************
 *  Rule #1
 *  COMMAND LINE -> COMPLETE_COMMAND PIPED_COMMAND
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/
int	cmd_line(t_token **cursor, t_data *data)
{
	if (((*cursor)->token_type >= E_HEREDOC
		 && (*cursor)->token_type <= E_OUTFILE) ||
		(*cursor)->token_type == E_WORD
		|| (*cursor)->token_type == E_DOULE_QUOTE
		|| (*cursor)->token_type == E_SINGLE_QUOTE)
	{
		data->parsing_stack = push(E_PIPED_COMMAND,data->parsing_stack);
		data->parsing_stack = push(E_COMPLETE_COMMAND,data->parsing_stack);
	}
	else if ((*cursor)->token_type == E_END_OF_TOKEN)
		return (1);
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #2
 *  PIPED_COMMAND -> PIPE COMPLETE_COMMAND PIPED_COMMAND
 *  Rule #3
 *  PIPED_COMMAND -> ε
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	piped_cmd(t_token **cursor, t_data *data)
{
	if ((*cursor)->token_type == E_PIPE)
	{
		data->parsing_stack = push(E_PIPED_COMMAND,data->parsing_stack);
		data->parsing_stack = push(E_COMPLETE_COMMAND,data->parsing_stack);
		data->parsing_stack = push(E_PIPE,data->parsing_stack);
		create_pipe_node(data,(*cursor));
	}
	else if ((*cursor)->token_type == E_END_OF_TOKEN)
		data->parsing_stack = push(E_EPSILON,data->parsing_stack);
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #4
 *  COMPLETE_COMMAND -> COMMAND_PREFIX COMMAND COMMAND_SUFFIX
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cpl_cmd(t_token **cursor, t_data *data)
{
	if (((*cursor)->token_type >= E_HEREDOC
		 && (*cursor)->token_type <= E_OUTFILE)
		|| (*cursor)->token_type == E_WORD
		|| (*cursor)->token_type == E_DOULE_QUOTE
		|| (*cursor)->token_type == E_SINGLE_QUOTE)
	{
		data->parsing_stack = push(E_COMMAND_SUFFIX,data->parsing_stack);
		data->parsing_stack = push(E_COMMAND,data->parsing_stack);
		data->parsing_stack = push(E_COMMAND_PREFIX,data->parsing_stack);
		//TODO CREATE COMMAND NODE
	} else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #10
 *  REDIRECTION -> REDIRECTION_OPERATOR WORD
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	redir(t_token **cursor, t_data *data)
{
	if ((*cursor)->token_type >= E_HEREDOC
		&& (*cursor)->token_type <= E_OUTFILE)
	{
		data->parsing_stack = push(E_WORD,data->parsing_stack);
		data->parsing_stack = push(E_REDIRECTION_OP,data->parsing_stack);
		create_redir_node(data,(*cursor));
	}
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}