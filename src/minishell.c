/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/10 20:01:44 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*data_init(void)
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
	t_data	*data;
	int		status;
	char	**new_env;

	new_env = create_env(env, argc, argv);
	while (1)
	{
		data = data_init();
		data->line = readline(PS1);
		if (!data->line)
		{
			exit(EXIT_FAILURE);
		}
		if (ft_strlen(data->line))
			add_history(data->line);
		lexer(data, new_env);
		status = parse(data);
		if (data->root && status == 1)
		{
			status = traverse_ast(data->root, &new_env);
			set_env(&new_env, "?", ft_itoa(status));
		}
	}
	return (0);
}
