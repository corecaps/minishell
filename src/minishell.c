/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/20 11:25:01 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void print_ast_debug(t_ast *node,int depth)
{
	int i;
	if (!node)
		return;
	i = 0;
	while (i++ < depth)
		printf("\t");
	printf("----------------------->\n");
	i = 0;
	while (i++ < depth)
		printf("\t");
	printf("Node type :\t");
	print_debug(node->type);
	if (node->type == E_REDIRECTION)
		printf("\t\tredir op[%s] redir file [%s]",node->token_node->value,node->token_node->next_token->value);
	else
		printf("\t\tcontent\t[%s]",node->token_node->value);
	printf("\n");
	if (node->left)
	{
		i = 0;
		while (i++ < depth)
			printf("\t");
		printf("[left] ->\n");
		print_ast_debug(node->left,depth+1);
	}
	else
	{
		i = 0;
		while (i++ < depth)
			printf("\t");
		printf("[left] -> [NULL]\n");
	}
	if (node->right)
	{
		i = 0;
		while (i++ < depth)
			printf("\t");
		printf("[right] ->\n");
		print_ast_debug(node->right,depth+1);
	}
	else
	{
		i = 0;
		while (i++ < depth)
			printf("\t");
		printf("[right] -> [NULL]\n");
	}
	i = 0;
	while (i++ < depth)
		printf("\t");
	printf("<-----------------------\n");
}

static	t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	return (data);
}
// TODO : signal handling
// TODO : prompt function
// TODO : proper exit
// TODO : leak fixing
int	main(int argc, char **argv, char **env)
{
	int		running;
	t_data	*data;
	int		debug;

	(void) argc;
	(void) argv;
	(void) env;
	running = 1;
	while (running)
	{
		data = data_init();
		data->line = readline(PS1);
		if (!data->line)
			exit(EXIT_FAILURE);
		if (ft_strlen(data->line))
			add_history(data->line);
		lexer(data);
		// printf("===========> Lexer tokens check: <===========\n");
		// while (data->start_token)
		// {
		// 	printf("Token type: %u\n", data->start_token->token_type);
		// 	printf("Token value: [%s]\n\n", data->start_token->value);
		// 	data->start_token = data->start_token->next_token;
		// }
		// printf("===========> Lexer token check ends <========\n");
		// printf("Line read : \n\t >> %s\n", data->line);
		// continue ;
		// exit(0);
		debug = parse(data);
//		if (debug == 1)
//		{
//			printf("Syntax Valid, AST built\n");
//			print_ast_debug(data->root,0);
//		}
//		else if (debug == -1)
//			printf("Memory error\n");
//		else if (debug == -2)
//			printf("Invalid Syntax\n");
//		else
//			printf("internal error\n");
		if (data->root && debug == 1)
		{
			if (data->root->type == E_PIPE)
				data->root->left->in_pipe = dup(0);
			debug = runner(data->root, env);
			printf("\n[Status:%d]\n",debug);
			del_ast(data->root);
		}
		//exit(0);
//		free_all(data);
	}
	return (0);
}
//need to handle add_token() in case NULL was returned