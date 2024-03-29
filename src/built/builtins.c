/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 04:37:58 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 10:27:17 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	builtins(t_cmd_tab cmd, bool in_child)
{
	if (cmd.cmd == NULL || cmd.cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd.cmd[0], "cd") == 0)
		ft_cd(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "pwd") == 0)
		ft_pwd(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "exit") == 0)
		ft_exit(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "export") == 0)
		ft_export(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "env") == 0)
		ft_env(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "unset") == 0)
		ft_unset(cmd, in_child);
	else if (ft_strcmp(cmd.cmd[0], "echo") == 0)
		ft_echo(cmd, in_child);
}
