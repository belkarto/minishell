/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:53:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/22 15:33:51 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
void	ft_exit(t_cmd_tab cmd)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	if (d_strlen(cmd.cmd) > 2)
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_meta.exit_status = 1;
		return ;
	}
	while (cmd.cmd[1] && cmd.cmd[1][++i])
	{
		if (ft_isdigit(cmd.cmd[1][i]) == 1)
			continue ;
		else
		{
			ft_putstr_fd(cmd.cmd[1], 2);
			ft_putstr_fd(" : numiric argument required\n", 2);
			exit (255);
		}
	}
	if (cmd.cmd[1] != NULL)
		num = ft_atoi(cmd.cmd[1]);
	exit(num);
}
