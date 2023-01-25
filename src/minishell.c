/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/25 14:21:16 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termios.h"

/******************************************************************************
 * Assure that the program is running in interactive mode
 * Set the signal handlers
 * Setups the terminal to not echo control characters
 * Create the environment
 *****************************************************************************/

char **initial_setup(int argc, char **argv, char **env)
{
	char **new_env;
	struct termios	term_info;

	if (!isatty(STDIN_FILENO))
	{
		write(2, "minishell works only in interactive mode\n", 41);
		exit(EXIT_FAILURE);
	}
	set_signals();
	tcgetattr(0, &term_info);
	term_info.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_info);
	new_env = create_env(env, argc, argv);
	return new_env;
}

/******************************************************************************
 * initialize the data struct and read the next command line
 * add the line to the history if it is not empty
 *****************************************************************************/

static t_data	*data_init(char ***env)
{
	t_data	*data;
	char	*prompt;

	data = (t_data *)gc_alloc(1,sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	prompt = get_prompt(env);
	data->line = readline(prompt);
	free(prompt);
	if (!data->line)
	{
		exit(EXIT_FAILURE);
	}
	gc_add(data->line);
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

	new_env = initial_setup(argc, argv, env);
	while (1)
	{
		data = data_init(&new_env);
		lexer(data, &new_env);
		status = parse(data);
		if (status < 0)
			parser_error(status);
		if (data->root && status == 1)
		{
			status = exec_cmd_line(data->root, &new_env, data->line);
			if (status < 0)
				exec_error(status);
		}
		else if (status == 1)
			status = 0;
		data->status = ft_itoa(status);
		gc_add(data->status);
		set_env(&new_env, "?", data->status);
		gc_free();
	}
}
