/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:14:18 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:34:37 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	sig_handler(int signum, siginfo_t *client_info, void *context)
{
	(void) context;
	(void) client_info;
	if (signum == SIGINT)
	{
		printf("\n");
		return ;
	}
}

void	set_signals(void)
{
	struct sigaction	handler;

	handler.sa_handler = SIG_IGN;
	sigemptyset(&handler.sa_mask);
	handler.sa_flags = 0;
	sigaction(SIGINT, &handler, NULL);
}
