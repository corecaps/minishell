/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_production.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:24:12 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/15 13:24:18 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 *  Rule #1
 *  COMMAND LINE -> COMPLETE_COMMAND PIPED_COMMAND
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/
int	cmd_line(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type == E_REDIRECTION ||
		(*cursor)->token_type == E_WORD)
	{
		(*stack) = push(E_PIPED_COMMAND,(*stack));
		(*stack) = push(E_COMPLETE_COMMAND,(*stack));
	}
	else
		return (-2);
	if ((*stack) == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #2
 *  PIPED_COMMAND -> PIPE COMPLETE COMMAND
 *  Rule #3
 *  PIPED_COMMAND -> ε
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	piped_cmd(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type == E_PIPE)
	{
		(*stack) = push(E_PIPED_COMMAND,(*stack));
		(*stack) = push(E_COMPLETE_COMMAND,(*stack));
		(*stack) = push(E_PIPE,(*stack));
	}
	else if ((*cursor)->token_type == E_END_OF_TOKEN)
		(*stack) = push(E_EPSILON,(*stack));
	else
		return (-2);
	if ((*stack) == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #4
 *  COMPLETE_COMMAND -> REDIRECTION COMMAND REDIRECTION COMMAND_ARG REDIRECTION
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	cpl_cmd(t_token **cursor, t_stack **stack)
{
	if (((*cursor)->token_type >= E_HEREDOC
		 && (*cursor)->token_type <= E_OUTFILE)
		|| (*cursor)->token_type == E_WORD)
	{
		(*stack) = push(E_REDIRECTION,(*stack));
		(*stack) = push(E_COMMAND_ARG,(*stack));
		(*stack) = push(E_REDIRECTION,(*stack));
		(*stack) = push(E_COMMAND,(*stack));
		(*stack) = push(E_REDIRECTION,(*stack));
	}
	if ((*stack) == NULL)
		return (-1);
	return (1);
}

/*******************************************************************************
 *  Rule #5
 *  REDIRECTION -> REDIRECTION_OPERATOR WORD
 *  Rule #6
 *  REDIRECTION -> ε
 * @return -1 in case of mem error
 * @return -2 in case of syntax error
 * @return 1 in case of success
 ******************************************************************************/

int	redir(t_token **cursor, t_stack **stack)
{
	if ((*cursor)->token_type >= E_HEREDOC
		&& (*cursor)->token_type <= E_OUTFILE)
	{
		// TODO Push instead of rules
		(*stack) = push(E_WORD,(*stack));
		(*stack) = push(E_REDIRECTION_OP,(*stack));
	}
	else
		(*stack) = push(E_EPSILON,(*stack));
	if ((*stack) == NULL)
		return (-1);
	return (1);
}