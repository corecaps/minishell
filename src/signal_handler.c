/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:14:18 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/28 10:30:43 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	sig_handler(int signum, siginfo_t *client_info, void *context)
{
	(void) context;
	(void) client_info;
	if (signum == SIGINT && client_info->si_pid != 0)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else if (signum == SIGINT && client_info->si_pid == 0)
	{
		write(2, "CTRL-C\n", 7);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT && client_info->si_pid == 0)
	{
		write(2, "Quit(Core Dumped)\n", 18);
		g_exit_status = 131;
	}
}

void	set_signals(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = sig_handler;
	sigemptyset(&handler.sa_mask);
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &handler, NULL);
	sigaction(SIGQUIT, &handler, NULL);
}
