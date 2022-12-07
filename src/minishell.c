/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/07 12:11:18 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		running;

	(void) argc;
	(void) argv;
	(void) env;
	running = 1;
	while (running)
	{
		line = readline(PS1);
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strlen(line))
			add_history(line);
		printf("Line read : \n\t >> %s\n", line);
		free(line);
	}
	return (0);
}
