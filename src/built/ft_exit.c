/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:53:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 10:17:02 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_numiric_argument(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : numiric argument required\n", 2);
	exit (255);
}

void	ft_exit(t_cmd_tab cmd, bool in_child)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	while (cmd.cmd[1] && cmd.cmd[1][++i])
	{
		if ((i == 0 && cmd.cmd[1][i] == '-') || (i == 0 && cmd.cmd[1][i] == '+')
			|| ft_isdigit(cmd.cmd[1][i]) == 1)
			continue ;
		else
			error_numiric_argument(cmd.cmd[1]);
	}
	if (d_strlen(cmd.cmd) > 2)
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_meta.exit_status = 1;
		if (in_child == true)
			exit (1);
		return ;
	}
	if (cmd.cmd[1] != NULL)
		num = ft_atoi(cmd.cmd[1]);
	exit(num);
}
