/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:27 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 18:18:59 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/******************************************************************************
 * Apply grammar rules on non terminal token pushing the right production
 * on parsing stack for the ll(1) predictive descent parser
 * @param non_terminal non terminal symbole poped from stack
 * @param cursor pointer to the current token in the linked list
 * @param stack pointer to the parsing stack
 * @return -3 in case of out of bound non terminal symbol
 * @return -2 in case of syntax error
 * @return -1 in case of memory error
 *****************************************************************************/

static int	get_prod(t_token_type non_terminal, t_token **cursor, t_data *data)
{
	int	result;
	int	(*prod[9])(t_token **, t_data *data);

	if (non_terminal > E_REDIRECTION_OP || non_terminal < E_COMMAND_LINE)
		return (-3);
	prod[0] = cmd_line;
	prod[1] = piped_cmd;
	prod[2] = cpl_cmd;
	prod[3] = cmd_prefix;
	prod[4] = cmd_suffix;
	prod[5] = redir;
	prod[6] = cmd;
	prod[7] = cmd_arg;
	prod[8] = redir_op;
	result = prod[non_terminal - E_COMMAND_LINE](cursor, data);
	return (result);
}

/*******************************************************************************
 * Recursive descent ll(1) parsing algorithm
 * token are define in t_token_type enum
 * token > E_NON_TERMINAL are non terminals token
 * token < E_NON_TERMINAL are terminals
 * E_EPSILON is ε (empty token)
 * E_END_OF_TOKEN is end of string TOKEN
 * Grammar in bnf form is :
 * COMMAND_LINE
 *                  : COMPLETE_COMMAND PIPED_CMD
 *                  ;
 *PIPED_CMD
 *                 : PIPE COMPLETE_COMMAND PIPED_CMD
 *                 |
 *                 ;
 *COMPLETE_COMMAND
 *                 : COMMAND_PREFIX COMMAND COMMAND_SUFFIX
 *                 ;
 *COMMAND_PREFIX
 *                 : REDIRECTION COMMAND_PREFIX
 *                 |
 *                 ;
 *COMMAND_SUFFIX
 *                 : REDIRECTION COMMAND_SUFFIX
 *                 | COMMAND_ARG COMMAND_SUFFIX
 *                 |
 *                 ;
 *REDIRECTION
 *                 : REDIRECTION_OP WORD
 *                 ;
 *COMMAND
 *                 : WORD
 *                 ;
 *COMMAND_ARG
 *                 : WORD
 *                 | SINGLE_QUOTE WORD DOUBLE_QUOTE
 *                 | DOUBLE_QUOTE WORD DOUBLE_QUOTE
 *                 ;
 *REDIRECTION_OP
 *                 : HEREDOC
 *                 | APPEND
 *                 | INFILE
 *                 | OUTFILE
 *                 ;
 * @param data data structure pointing to the parsed string and the token list
 * @param data and the AST structure
 * @return -3 in case of out of bound non terminal symbol
 * @return -2 in case of syntax error
 * @return -1 in case of memory error
 * @return 1 in case of success
 */

int	parse(t_data *data)
{
	t_token_type	state;
	t_token			*cursor;
	int				result;

	cursor = data->start_token;
	data->root = NULL;
	data->current = NULL;
	data->parsing_stack = push(E_END_OF_TOKEN, NULL);
	data->parsing_stack = push(E_COMMAND_LINE, data->parsing_stack);
	if (data->parsing_stack == NULL)
		return (-1);
	while (count_stack(data->parsing_stack))
	{
		if (data->parsing_stack->type == E_END_OF_TOKEN)
			break ;
		if (data->parsing_stack->type > E_NON_TERMINALS)
		{
			state = pop(&data->parsing_stack);
			if (state >= E_END_OF_TOKEN)
				return (-3);
			result = get_prod(state, &cursor, data);
			if (result < 0)
				return (result);
		}
		else
		{
			state = pop(&data->parsing_stack);
			if (state == E_EPSILON)
				continue ;
			if (cursor->token_type == state)
				cursor = cursor->next_token;
			else
				return (-2);
		}
	}
	if (cursor && cursor->token_type != E_END_OF_TOKEN)
		return (-2);
	return (1);
}
