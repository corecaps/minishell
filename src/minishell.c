/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/09 14:19:34 by latahbah         ###   ########.fr       */
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
		printf("Line read : \n\t >> %s\n", data.line);
		free(data.line);
	}
	return (0);
}
