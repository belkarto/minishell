/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 04:37:58 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/16 09:13:51 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	execut_she(t_cmd_tab cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd.env, cmd.cmd, env) == -1)
			perror("execve");
		exit(127);
	}
	waitpid(pid, NULL, 0);
}

void	builtins(t_cmd_tab cmd)
{
	if (cmd.cmd == NULL)
		return ;
	if (ft_strcmp(cmd.cmd[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd.cmd[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd.cmd[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd.cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd.cmd[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd.cmd[0], "unset") == 0)
		ft_unset(cmd);
}
