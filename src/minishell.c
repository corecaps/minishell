/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/08 18:08:42 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	int		running;
	t_data	data;

	(void) argc;
	(void) argv;
	(void) env;
	running = 1;
	while (running)
	{
		data.line = readline(PS1);
		data.start_line = data.line;
		if (!data.line)
			exit(EXIT_FAILURE);
		if (ft_strlen(data.line))
			add_history(data.line);
		get_tokens(&data);
		printf("Line read : \n\t >> %s\n", data.start_line);
		//test
		// t_token	*test_token;
		// test_token = data.start_token;
		// printf("Parsed tokens:\n");
		// while (test_token)
		// {
		// 	printf("%s\n", test_token->value);
		// 	test_token = test_token->next_token;
		// }
		// printf("\n\n");
		free(data.start_line);
	}
	return (0);
}
