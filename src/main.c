/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/02/26 21:31:31 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"
#include <signal.h>
#include <sys/signal.h>

void	init_program(int argc, char *argv[], char **env)
{
	if (argc != 1)
		exit (1);
	(void) argv;
	(void) env;
}

void handle_sigint(int sig)
{
	(void)sig;
	exit(0);
}

void	ignore(int sig)
{
	(void)sig;
	ft_printf("\n\033[0;1;3;32m MINISHELL $> \033[0;37m");
}

int main(int argc, char *argv[], char **env)
{
	init_program(argc, argv, env);
	signal(SIGINT, ignore);
	signal(SIGQUIT, handle_sigint);
	while (1)
	{
		readline("\033[0;1;3;32m MINISHELL $> \033[0;37m");
	}
	return (0);
}
