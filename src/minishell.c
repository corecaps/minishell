/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/12 17:48:11 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	data->line = readline(PS1);
	if (!data->line)
	{
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(data->line))
		add_history(data->line);
	garbage_collector_add(data->line);
	garbage_collector_add(data);
	return (data);
}
// TODO : signal handling
// TODO : prompt function
void gc_ast_del(t_ast *current)
{
	if (current->left)
		gc_ast_del(current->left);
	if (current->right)
		gc_ast_del(current->right);
	garbage_collector_add(current);
}

void gc_pre_exec(t_data * data)
{
	t_token	*token_cursor;
	t_stack	*stack_cursor;

	token_cursor = data->start_token;
	while (token_cursor)
	{
	garbage_collector_add(token_cursor->value);
	garbage_collector_add(token_cursor);
	token_cursor = token_cursor->next_token;
	}
	gc_ast_del(data->root);
	stack_cursor = data->parsing_stack;
	while (stack_cursor)
	{
		garbage_collector_add(stack_cursor);
		stack_cursor = stack_cursor->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		status;
	char	**new_env;

//	set_signals();
	new_env = create_env(env, argc, argv);
	while (1)
	{
		data = data_init();
		lexer(data, &new_env);
		status = parse(data);
		if (data->root && status == 1)
		{
			gc_pre_exec(data);
			status = exec_cmd_line(data->root, &new_env);
			data->status = ft_itoa(status);
			set_env(&new_env, "?", data->status);
		}
		else
		{
			data->status = ft_itoa(status);
			set_env(&new_env, "?",data->status);
		}free_data(data);
	}
	free_env(new_env);
	return (0);
}