/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/23 10:52:31 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*data_init(char ***env)
{
	t_data	*data;
	char	*prompt;

	data = (t_data *)malloc(sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	prompt = get_prompt(env);
	data->line = readline(prompt);
	free(prompt);
	if (!data->line)
	{
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(data->line))
		add_history(data->line);
	return (data);
}

void	interactive_mode_assert(void)
{
	perror("minishell works only in interactive mode\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		status;
	char	**new_env;

//	set_signals();
	if (!isatty(STDIN_FILENO))
		interactive_mode_assert();
	new_env = create_env(env, argc, argv);
	while (1)
	{
		data = data_init(&new_env);
		lexer(data, &new_env);
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
			set_env(&new_env, "?", data->status);
		}
		free_data(data);
	}
}
