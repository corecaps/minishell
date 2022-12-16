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

/*******************************************************************************
 *  Rule #7
 *  COMMAND -> WORD
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cmd(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type == E_WORD)
	{
		(*stack) = push(E_WORD,(*stack));
	}
	else
		return (-2);
	if ((*stack) == NULL)
		return (-1);
	return (1);
}

static void rule_nine(t_token *const *cursor, t_stack **stack)
{
	(*stack) = push(E_COMMAND_ARG, (*stack));
	(*stack) = push(E_REDIRECTION,(*stack));
	(*stack) = push((*cursor)->token_type,(*stack));
	(*stack) = push(E_WORD,(*stack));
	(*stack) = push((*cursor)->token_type,(*stack));
}

static void rule_eight(t_stack **stack)
{
	(*stack) = push(E_COMMAND_ARG, (*stack));
	(*stack) = push(E_REDIRECTION,(*stack));
	(*stack) = push(E_WORD,(*stack));
}

/*******************************************************************************
 *  Rule #8
 *  COMMAND_ARG -> WORD REDIRECTION COMMAND_ARG
 *  Rule #9
 *  COMMAND_ARG -> SINGLE_QUOTE WORD SINGLE_QUOTE REDIRECTION COMMAND_ARG
 *  Rule #10
 *  COMMAND_ARG -> DOUBLE_QUOTE WORD DOUBLE_QUOTE REDIRECTION COMMAND_ARG
 *  Rule #11
 *  COMMAND_ARG -> REDIRECTION
 *
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cmd_arg(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type == E_WORD)
		rule_eight(stack);
	else if (((*cursor)->token_type == E_SINGLE_QUOTE)
			 ||((*cursor)->token_type == E_DOULE_QUOTE))
		rule_nine(cursor, stack);
	else if ((*cursor)->token_type >= E_HEREDOC
			 && (*cursor)->token_type <= E_OUTFILE)
		(*stack) = push(E_REDIRECTION,(*stack));
	else
		(*stack) = push(E_EPSILON,(*stack));
	if ((*stack) == NULL)
		return (-1);
	return (1);
}


/*******************************************************************************
 *  Rule #12
 *  REDIRECTION_OP -> HERE_DOC
 *  Rule #12
 *  REDIRECTION_OP -> APPEND
 *  Rule #12
 *  REDIRECTION_OP -> INFILE
 *  Rule #12
 *  REDIRECTION_OP -> OUTFILE
 *
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	redir_op(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type == E_HEREDOC)
		(*stack) = push(E_HEREDOC,(*stack));
	else if ((*cursor)->token_type == E_APPEND)
		(*stack) = push(E_APPEND,(*stack));
	else if ((*cursor)->token_type == E_INFILE)
		(*stack) = push(E_INFILE,(*stack));
	else if ((*cursor)->token_type == E_OUTFILE)
		(*stack) = push(E_OUTFILE,(*stack));
	else
		return (-2);
	if ((*stack) == NULL)
		return (-1);
	return (1);
}