/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/19 10:20:43 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	int		running;
	t_data	*data;
	int		debug;
	t_token *bottom;

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
		printf("Line read : \n\t >> %s\n", data->line);
		debug = parse(data);
		printf("Parser return :%d\n",debug);
		//exit(0);
//		free_all(data);
	}
	return (0);
}
//need to handle add_token() in case NULL was returned
