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
	if ((*cursor)->token_type == E_REDIRECTION ||
		(*cursor)->token_type == E_WORD)
	{
		// TODO Push instead of rules
		(*stack) = push(E_PIPED_COMMAND,(*stack));
		(*stack) = push(E_COMPLETE_COMMAND,(*stack));
		(*stack) = push(E_END_OF_TOKEN,(*stack));
	}
	if ((*stack) == NULL)
		return (-1);
	return (1);
}

int	redir_op(t_token **cursor, t_stack **stack)
{
	int	result;

	if ((*cursor)->token_type == E_REDIRECTION ||
		(*cursor)->token_type == E_WORD)
	{
		// TODO Push instead of rules
		(*stack) = push(E_PIPED_COMMAND,(*stack));
		(*stack) = push(E_COMPLETE_COMMAND,(*stack));
		(*stack) = push(E_END_OF_TOKEN,(*stack));
	}
	if ((*stack) == NULL)
		return (-1);
	return (1);
}