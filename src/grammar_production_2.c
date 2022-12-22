/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_production_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:26:51 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/15 13:27:04 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*******************************************************************************
 *  Rule #5
 *  COMMAND_PREFIX -> REDIRECTION COMMAND_PREFIX
 *  Rule #6
 *  COMMAND_PREFIX -> ε
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cmd_prefix(t_token **cursor, t_data *data)
{
	if ((*cursor)->token_type == E_WORD
		|| (*cursor)->token_type == E_DOULE_QUOTE
		|| (*cursor)->token_type == E_SINGLE_QUOTE)
	{
		data->parsing_stack = push(E_EPSILON, data->parsing_stack);
	}
	else if ((*cursor)->token_type >= E_HEREDOC
			 && (*cursor)->token_type <= E_OUTFILE)
	{
		data->parsing_stack = push(E_COMMAND_PREFIX,data->parsing_stack);
		data->parsing_stack = push(E_REDIRECTION,data->parsing_stack);
	}
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #7
 *  COMMAND_SUFFIX -> REDIRECTION COMMAND_SUFFIX
 *  Rule #8
 *  COMMAND_SUFFIX -> COMMAND_ARG COMMAND_SUFFIX
 *  Rule #9
 *  COMMAND_PREFIX -> ε
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ********** ********************************************************************/

int	cmd_suffix(t_token **cursor, t_data *data)
{
	if ((*cursor)->token_type == E_PIPE
		|| (*cursor)->token_type == E_END_OF_TOKEN)
		data->parsing_stack = push(E_EPSILON, data->parsing_stack);
	else if ((*cursor)->token_type >= E_HEREDOC
			 && (*cursor)->token_type <= E_OUTFILE)
	{
		data->parsing_stack = push(E_COMMAND_SUFFIX,data->parsing_stack);
		data->parsing_stack = push(E_REDIRECTION,data->parsing_stack);
	}
	else if ((*cursor)->token_type == E_WORD
		|| (*cursor)->token_type == E_SINGLE_QUOTE
		|| (*cursor)->token_type == E_DOULE_QUOTE)
	{
		data->parsing_stack = push(E_COMMAND_SUFFIX,data->parsing_stack);
		data->parsing_stack = push(E_COMMAND_ARG,data->parsing_stack);
	}
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #11
 *  COMMAND -> WORD
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cmd(t_token **cursor, t_data *data)
{
	if ((*cursor)->token_type == E_WORD)
	{
		data->parsing_stack = push(E_WORD, data->parsing_stack);
		create_cmd_node(data,(*cursor));
	}
	else if (((*cursor)->token_type == E_SINGLE_QUOTE)
			 ||((*cursor)->token_type == E_DOULE_QUOTE))
	{
		data->parsing_stack = push((*cursor)->token_type,data->parsing_stack);
		data->parsing_stack = push(E_WORD,data->parsing_stack);
		data->parsing_stack = push((*cursor)->token_type,data->parsing_stack);
		create_cmd_node(data,(*cursor)->next_token);
	}
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #12
 *  COMMAND_ARG -> WORD
 *  Rule #13
 *  COMMAND_ARG -> SINGLE_QUOTE WORD SINGLE_QUOTE
 *  Rule #14
 *  COMMAND_ARG -> DOUBLE_QUOTE WORD DOUBLE_QUOTE
 *
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cmd_arg(t_token **cursor, t_data *data)
{
	t_token *token;

	token = (*cursor);
	if ((*cursor)->token_type == E_WORD)
		data->parsing_stack = push(E_WORD,data->parsing_stack);
	else if (((*cursor)->token_type == E_SINGLE_QUOTE)
		||((*cursor)->token_type == E_DOULE_QUOTE))
	{
		data->parsing_stack = push((*cursor)->token_type,data->parsing_stack);
		data->parsing_stack = push(E_WORD,data->parsing_stack);
		data->parsing_stack = push((*cursor)->token_type,data->parsing_stack);
		token = token->next_token;
	}
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	create_cmd_arg_node(data,token);
	return (1);
}


/*******************************************************************************
 *  Rule #15
 *  REDIRECTION_OP -> HERE_DOC
 *  Rule #16
 *  REDIRECTION_OP -> APPEND
 *  Rule #17
 *  REDIRECTION_OP -> INFILE
 *  Rule #18
 *  REDIRECTION_OP -> OUTFILE
 *
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	redir_op(t_token **cursor, t_data *data)
{

	if ((*cursor)->token_type == E_HEREDOC)
		data->parsing_stack = push(E_HEREDOC,data->parsing_stack);
	else if ((*cursor)->token_type == E_APPEND)
		data->parsing_stack = push(E_APPEND,data->parsing_stack);
	else if ((*cursor)->token_type == E_INFILE)
		data->parsing_stack = push(E_INFILE,data->parsing_stack);
	else if ((*cursor)->token_type == E_OUTFILE)
		data->parsing_stack = push(E_OUTFILE,data->parsing_stack);
	else
		return (-2);
	if (data->parsing_stack == NULL)
		return (-1);
	return (1);
}