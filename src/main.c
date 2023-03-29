/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/22 15:44:28 by ohalim           ###   ########.fr       */
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
	g_meta.exit_status = 0;
	printf("\n\t	-USE AT YOUR OWN RISK-	\n\n");
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
}

int	main(int argc, char **argv, char **env)
{
	char	*readed;
	t_cmd_tab	**ok;

	init_program(argc, argv, env);
	signals();
	t_cmd_tab cmd;
	while (1)
	{
		// printf("%d\n", g_meta.exit_status);
		readed = readline("\033[0;1;3;32m MINISHELL $> \033[0;37m");
		ft_add_history(readed);
		ok = command_table(readed);
		free(ok);
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
