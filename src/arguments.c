//
// Created by corecaps on 04/01/23.
//
#include "minishell.h"
#include "exec.h"

int count_args(t_ast *command_node)
{
	int argc;
	t_ast *cursor;

	argc = 0;
	cursor = command_node->right;
	while(cursor)
	{
		argc ++;
		cursor = cursor->left;
	}
	return argc;
}

char **get_args(t_ast *command_node)
{
	char	**argv;
	int		argc;
	int		i;
	t_ast	*cursor;

	if (command_node == NULL || command_node->type != E_COMMAND )
		return (NULL);
	argc = count_args(command_node);
	argv = malloc(sizeof(char *)*(argc + 2));
	if (argv == NULL)
		return (NULL);
	argv[0] = command_node->token_node->value;
	i = 0;
	cursor = command_node->right;
	while (i < argc)
	{
		argv[i+1] = cursor->token_node->value;
		cursor = cursor->left;
		i++;
	}
	argv[i+1] = 0;
	return (argv);
}