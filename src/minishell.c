/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:29:54 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termios.h"

void	setup_term(void)
{
	struct termios	term_info;

	tcgetattr(0, &term_info);
	term_info.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_info);
}

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

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		status;
	char	**new_env;

	if (!isatty(STDIN_FILENO))
	{
		write(2, "minishell works only in interactive mode\n", 41);
		exit(EXIT_FAILURE);
	}
	set_signals();
	setup_term();
	new_env = create_env(env, argc, argv);
	while (1)
	{
		data = data_init(&new_env);
		lexer(data, &new_env);
		status = parse(data);
		if (status < 0)
			parser_error(status);
		if (data->root && status == 1)
		{
			status = exec_cmd_line(data->root, &new_env);
			if (status < 0)
				exec_error(status);
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