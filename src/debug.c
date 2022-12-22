//
// Created by corecaps on 20/12/22.
//

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
		case E_COMMAND_PREFIX:
			printf("[COMMAND PREFIX]");
			break;
		case E_COMMAND_SUFFIX:
			printf("[COMMAND SUFFIX]");
			break;
		case E_REDIRECTION:
			printf("[REDIRECTION]");
			break;
		case E_COMMAND:
			printf("[COMMAND]");
			break;
		case E_COMMAND_ARG:
			printf("[COMMAND_ARG]");
			break;
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

void print_ast_debug(t_ast *node)
{
	if (!node)
		return;
	printf("Node type :\t");
	print_debug(node->type);
	printf("\t\tcontent\t[%s]",node->token_node->value);
	printf("\n");
	if (node->left)
	{
		printf("----------------------->\n");
		printf("[left] ->\n");
		print_ast_debug(node->left);
	}
	if (node->right)
	{
		printf("----------------------->\n");
		printf("[right] ->\n");
		print_ast_debug(node->right);
	}
}