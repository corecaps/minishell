/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/12 15:08:17 by latahbah         ###   ########.fr       */
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
		if (!data.line)
			exit(EXIT_FAILURE);
		if (ft_strlen(data.line))
			add_history(data.line);
		lexer(&data);
		printf("Token count - %d\n", count_token(data.start_token));
		while (data.start_token)
		{
			printf("Token value: [%s]\n", data.start_token->value);
			data.start_token = data.start_token->next_token;
		}
		printf("Line read : \n\t >> %s\n", data.line);
		//exit(0);
		free_all(&data);
	}
	return (0);
}
//need to handle add_token() in case NULL was returned


