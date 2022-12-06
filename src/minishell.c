/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/05 11:13:50 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	char *line;
	int running;

	running = 1;
	while (running)
	{
		line = readline("Minishell\t% ");
		if (ft_strlen(line))
			add_history(line);
		printf("Line read : \n\t >> %s\n",line);
		free(line);
	}
	return (0);
}