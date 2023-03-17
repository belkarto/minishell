/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/17 05:09:57 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

t_data	g_meta;

void	init_program(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_meta.env = init_env(env);
	g_meta.ex_statu = 0;
	printf("\n\t  -USE AT YOUR OWN RISK-\n");
}

static int	ft_str_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_add_history(char *str)
{
	if (str && ft_strlen(str) && ft_str_space(str))
		add_history(str);
}

void	set_struct(char *readed, t_cmd_tab *cmd)
{
	cmd->cmd = ft_split(readed, ' ');
	cmd->env = ft_strjoin("/bin/", cmd->cmd[0]);
	cmd->in_file = 0;
	cmd->out_file = 1;
}

int	main(int argc, char **argv, char **env)
{
	char	*readed;

	init_program(argc, argv, env);
	signals();
	t_cmd_tab cmd;
	while (1)
	{
		readed = readline("\033[0;1;3;32m MINISHELL $> \033[0;37m");
		ft_add_history(readed);
		parsing_input(readed);
		set_struct(readed, &cmd);
		builtins(cmd, env);
		free(cmd.env);
		free(cmd.cmd[0]);
		free(cmd.cmd[1]);
		free(cmd.cmd);
		free(readed);
	}
	return (0);
}
