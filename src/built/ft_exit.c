/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:53:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 09:36:02 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_numiric_argument(char *num)
{
	ft_putstr_fd(num, 2);
	ft_putstr_fd(" : numiric argument required\n", 2);
	exit (255);
}

static int	check_is_number(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
	{
		if ((i == 0 && num[i] == '-') || (i == 0 && num[i] == '+')
			|| ft_isdigit(num[i]) == 1)
			continue ;
		else
			return (1);
	}
	return (0);
}

static int	check_number(char *num)
{
	if (num == NULL)
		return (0);
	if (check_is_number(num) == 1)
		return (1);
	if (*num == '-')
	{
		++num;
		if (*num == '\0' || ft_strlen(num) > ft_strlen("9223372036854775808")
			|| (ft_strlen(num) == ft_strlen("9223372036854775808")
				&& ft_strcmp(num, "9223372036854775808") > 0))
			return (1);
	}
	else
	{
		if (*num == '+')
			++num;
		if (*num == '\0' || ft_strlen(num) > ft_strlen("9223372036854775807")
			|| (ft_strlen(num) == ft_strlen("9223372036854775807")
				&& ft_strcmp(num, "9223372036854775807") > 0))
		{
			return (1);
		}
	}
	return (0);
}

void	ft_exit(t_cmd_tab cmd, bool in_child)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	if (check_number(cmd.cmd[1]) == 1)
		error_numiric_argument(cmd.cmd[1]);
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
