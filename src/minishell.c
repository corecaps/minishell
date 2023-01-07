/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/22 14:48:36 by latahbah         ###   ########.fr       */
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
// TODO : signal handling
// TODO : prompt function
// TODO : proper exit
// TODO : leak fixing

int	main(int argc, char **argv, char **env)
{
	int		running;
	t_data	*data;
//	int		pid;
	int		status;
	char	**new_env;

	running = 1;
	new_env = create_env(env, argc, argv);
	while (running)
	{
		data = data_init();
		data->line = readline(PS1);
		if (!data->line)
			exit(EXIT_FAILURE);
		if (ft_strlen(data->line))
			add_history(data->line);
		lexer(data);
		status = parse(data);
		if (data->root && status == 1)
		{
//			pid = fork(); // TODO Move the fork to the exec function
//			if (pid < 0)
//				perror("fork error\n");
//			else if (pid == 0)
//			{
				status = traverse_ast(data->root, &new_env);
				printf("\n[Status:%d]\n", status);
				if (status == -3)
					printf("Command [%s] not found\n", data->root->token_node->value);
//			}
//			else
//			{
//				waitpid(pid,&status,0);
//				if (status != 0)
//					fprintf(stderr,"Error :[%d] \n", status);
//			}
			del_ast(data->root);
		}
	}
	return (0);
}