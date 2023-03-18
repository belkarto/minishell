/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 04:37:58 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/18 08:17:51 by belkarto         ###   ########.fr       */
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

void	builtins(t_cmd_tab cmd, char **env)
{
	if (ft_strncmp(cmd.cmd[0], "cd", ft_strlen(cmd.cmd[0])) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd.cmd[0], "pwd", ft_strlen(cmd.cmd[0])) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(cmd.cmd[0], "exit", ft_strlen(cmd.cmd[0])) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd.cmd[0], "export", ft_strlen(cmd.cmd[0])) == 0)
		ft_export(cmd);
	else if (ft_strncmp(cmd.cmd[0], "env", ft_strlen(cmd.cmd[0])) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd.cmd[0], "unset", ft_strlen(cmd.cmd[0])) == 0)
		ft_unset(cmd);
	else
		execut_she(cmd, env);
}
