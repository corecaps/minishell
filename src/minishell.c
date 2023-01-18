/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/18 11:19:17 by latahbah         ###   ########.fr       */
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
		//FOR TEST
		// printf("Token List:\n");
		// while (data->start_token)
		// {
		// 	printf("[%s]\n", data->start_token->value);
		// 	data->start_token = data->start_token->next_token;
		// }
		// exit(0);
		//
		status = parse(data);
		if (data->root && status == 1)
		{
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
	free_env(&new_env);
	return (0);
}