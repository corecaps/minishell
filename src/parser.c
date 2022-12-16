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

void print_debug(t_token_type type)
{
	switch (type)
	{
		case E_COMMAND_LINE:
			printf("[COMMAND_LINE]");
			break;
		case E_PIPED_COMMAND:
			printf("[PIPED_COMMAND]");
			break;
		case E_COMPLETE_COMMAND:
			printf("[COMPLETE COMMAND]");
			break;
		case E_REDIRECTION:
			printf("[REDIRECTION]");
			break;
		case E_COMMAND:
			printf("[COMMAND]");
			break;
		case E_COMMAND_ARG:
			printf("[COMMAND_ARG]");
		case E_PIPE:
			printf("[PIPE]");
			break;
		case E_REDIRECTION_OP:
			printf("[REDIR OP]");
			break;
		case E_WORD:
			printf("[WORD]");
			break;
		case E_SINGLE_QUOTE:
			printf("[SQUOTE]");
			break;
		case E_DOULE_QUOTE:
			printf("[DQUOTE]");
			break;
		case E_HEREDOC:
			printf("[<<]");
			break;
		case E_APPEND:
			printf("[>>]");
			break;
		case E_INFILE:
			printf("[<]");
			break;
		case E_OUTFILE:
			printf("[>]");
			break;
		case E_EPSILON:
			printf("[]");
			break;
		case E_END_OF_TOKEN:
			printf("[END]");
			break;
		default:
			printf("[[?]]");
	}
}
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

	printf("Applying rules for ");
	print_debug(non_terminal);
	printf("non terminal\n");
	printf("cursor token type :");
	print_debug((*cursor)->token_type);
	printf("  value %s\n",(*cursor)->value);
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
	t_stack			*debug;
	cursor = data->start_token;
	parsing_stack = push(E_END_OF_TOKEN, NULL);
	parsing_stack = push(E_COMMAND_LINE, parsing_stack);
	printf("Parsing token list size : [%d]\n", count_token(data->start_token));
	if (parsing_stack == NULL)
		return (-1);
	while (count_stack(parsing_stack))
	{
		if (parsing_stack->type == E_END_OF_TOKEN)
			break;
		if (parsing_stack->type > E_NON_TERMINALS)
		{
			// TODO Extract method here
			state = pop(&parsing_stack);
			printf("current State :");
			print_debug(state);
			printf("\n");
			printf("Current Stack Size : %d\n", count_stack(parsing_stack));
			debug = parsing_stack;
			while (debug)
			{
				print_debug(debug->type);
				debug =debug->next;
			}
			printf("\n");
			if (state >= E_END_OF_TOKEN)
				return (-3);
			result = get_prod(state, &cursor,
								&parsing_stack);
			if (result < 0)
				return (result);
			printf("===New Prod added====");
			printf("Current Stack Size : %d\n", count_stack(parsing_stack));
			debug = parsing_stack;
			while (debug)
			{
				print_debug(debug->type);
				debug =debug->next;
			}
			printf("\n");
		}
		else
		{
			// TODO extract method here
			state = pop(&parsing_stack);
			if (state == E_EPSILON)
			{
				printf("[]->Epsilonn -> Poped empty\n");
				continue;
			}
			if (cursor->token_type == state)
			{
				printf("\n==============================================\n");
				printf("========Validating ");
				print_debug(state);
				printf(" [%s]===========\n",cursor->value);
				printf("==============================================\n\n");
				cursor = cursor->next_token;

				// TODO Create AST Node here
			}
			else
				return (-2);
		}
	}
	if (cursor && cursor->token_type != E_END_OF_TOKEN)
		return (-2);
	return (1);
}