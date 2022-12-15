/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:27 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/14 11:03:38 by jgarcia          ###   ########.fr       */
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
 ******************************************************************************/

static int	get_prod(t_token_type non_terminal, t_token **cursor, t_stack **stack)
{
	int	result;
	int (*prod[7])(t_token **,t_stack **stack);

	if (non_terminal > E_REDIRECTION_OP || non_terminal < E_COMMAND_LINE)
		return (-3);
	prod[0] = cmd_line;
	prod[1] = piped_cmd;
	prod[2] = cpl_cmd;
	prod[3] = redir;
	prod[4] = cmd;
	prod[5] = cmd_arg;
	prod[6] = redir_op;
	result = prod[non_terminal-E_COMMAND_LINE](cursor,stack);
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
 *                 : REDIRECTION CMD REDIRECTION CMD_ARG REDIRECTION
 *                 ;
 *REDIRECTION
 *                 : REDIRECTION_OP WORD
 *                 |
 *                 ;
 *CMD
 *                  : WORD
 *                 ;
 *CMD_ARG
 *                  : WORD REDIRECTION CMD_ARG
 *                 | SINGLE_QUOTE WORD DOUBLE_QUOTE REDIRECTION CMD_ARG
 *                 | DOUBLE_QUOTE WORD DOUBLE_QUOTE REDIRECTION CMD_ARG
 *                 | REDIRECTION
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
	t_stack			*parsing_stack;
	t_token_type	state;
	t_token			*cursor;
	int				result;

	cursor = data->start_token;
	parsing_stack = push(E_COMMAND_LINE, NULL);
	if (parsing_stack == NULL)
		return (-1);
	while (count_stack(parsing_stack) && cursor)
	{
		if (parsing_stack->type > E_NON_TERMINALS)
		{
			// TODO Extract method here
			state = pop(&parsing_stack);
			if (state >= E_END_OF_TOKEN)
				return (-3);
			result = get_prod(state, &cursor,
								&parsing_stack);
			if (result < 0)
				return (result);
		}
		else
		{
			// TODO extract method here
			state = pop(&parsing_stack);
			if (state == E_EPSILON)
				continue ;
			if (cursor->token_type == state)
				cursor = cursor->next_token;
				// TODO Create AST Node here
			else
				return (-2);
		}
	}
	return (1);
}