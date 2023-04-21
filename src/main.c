/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/21 11:18:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_data	g_meta;

void	init_program(int ac, char **av, char **env)
{
	struct termios term;

	(void)ac;
	(void)av;
	g_meta.env = init_env(env);
	g_meta.exit_status = 0;
	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\n\t	-USE AT YOUR OWN RISK-	\n\n");
}

static int	ft_str_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_add_history(char *str)
{
	if (!str)
		exit(0);
	if (str && ft_strlen(str) && ft_str_space(str))
	{
		add_history(str);
		return (0);
	}
	else
	{
		free(str);
		return (1);
	}
}

void	ft_wait_pid(pid_t *pid, int len)
{
	int	i;

	i = -1;
	if (!pid)
		return ;
	while (++i < len)
		waitpid(pid[i], &g_meta.exit_status, 0);
	g_meta.exit_status = WEXITSTATUS(g_meta.exit_status);
}

int	main(int argc, char **argv, char **env)
{
	char	*readed;
	t_cmd_tab	*cmd_tab;
	pid_t		*pid;

	init_program(argc, argv, env);
	signals();
	while (1)
	{
		readed = readline("\033[0;1;3;32m MINISHELL $> \033[0;37m");
		if (ft_add_history(readed) == 1)
			continue ;
		cmd_tab = command_table(readed);
		// print_cmd_tab(cmd_tab);
		pid = exec_cmd_tab(cmd_tab, env);
		ft_wait_pid(pid, cmd_tab->len);
		cmd_tab_free(&cmd_tab);
		free(pid);
		free(readed);
	}
	(void)pid;
	return (0);
}
