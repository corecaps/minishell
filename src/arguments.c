/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:36:36 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 18:41:28 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*******************************************************************************
 * Count the number of arguments childs of a E_COMMAND node
 * @param command_node Node of type E_COMMAND
 * @return number of arguments
 *****************************************************************************/

int	count_args(t_ast *command_node)
{
	int		argc;
	t_ast	*cursor;

	argc = 0;
	cursor = command_node->right;
	while (cursor)
	{
		argc ++;
		cursor = cursor->left;
	}
	return (argc);
}

/******************************************************************************
 * Create an array of arguments from a E_COMMAND node
 * @param command_node Node of type E_COMMAND
 * @return argv array
 *****************************************************************************/

char	**get_args(t_ast *command_node)
{
	char	**argv;
	int		argc;
	int		i;
	t_ast	*cursor;

	if (command_node == NULL || command_node->type != E_COMMAND)
		return (NULL);
	argc = count_args(command_node);
	argv = malloc(sizeof(char *) * (argc + 2));
	gc_add(argv);
	if (argv == NULL)
		return (NULL);
	argv[0] = command_node->token_node->value;
	i = 0;
	cursor = command_node->right;
	while (i < argc)
	{
		argv[i + 1] = cursor->token_node->value;
		cursor = cursor->left;
		i++;
	}
	argv[i + 1] = 0;
	return (argv);
}