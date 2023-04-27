/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:28:31 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 12:08:03 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>
#include <sys/signal.h>

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_meta.exit_status = 1;
}

void	end_of_file(void)
{
	ft_printf("\r\035[0;1;3;38m MINISHELL $>\033[0;37m exit\n");
	exit(0);
}

void	signals(void)
{
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);
}
