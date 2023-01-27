/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:05 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 15:31:53 by jgarcia          ###   ########.fr       */
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

static void	initial_setup(int argc, char **argv, char **env)
{
	struct termios	term_info;
	char			*cwd;

	if (!isatty(STDIN_FILENO))
	{
		write(2, "minishell works only in interactive mode\n", 41);
		exit(EXIT_FAILURE);
	}
	set_signals();
	tcgetattr(0, &term_info);
	term_info.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_info);
	if (!create_env(env, argc, argv))
		exit(EXIT_FAILURE);
	cwd = get_env("PWD", gc_env_alloc(-1));
	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		set_env("PWD", cwd);
		free(cwd);
	}
	else
		free(cwd);
}

/******************************************************************************
 * initialize the data struct and read the next command line
 * add the line to the history if it is not empty
 *****************************************************************************/

static t_data	*data_init(void)
{
	t_data	*data;
	char	*prompt;

	data = (t_data *)gc_alloc(1, sizeof(t_data));
	data->open_quote = -1;
	data->start_token = NULL;
	prompt = get_prompt(gc_env_alloc(-1));
	data->line = readline(prompt);
	free(prompt);
	if (!data->line)
	{
		gc_env_free();
		gc_free();
		exit(0);
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
	int		old_status;

	old_status = 0;
	initial_setup(argc, argv, env);
	while (1)
	{
		data = data_init();
		lexer(data, gc_env_alloc(-1));
		status = parse(data);
		parser_error(&status);
		if (data->root && status == 1)
		status = exec_cmd_line(data->root, gc_env_alloc(-1), data->line);
		exec_error(&status);
		if (status == 1)
			status = old_status;
		data->status = ft_itoa(status);
		gc_add(data->status);
		old_status = status;
		set_env("?", data->status);
		gc_free();
	}
}
