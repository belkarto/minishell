/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 04:37:58 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/13 05:35:54 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/wait.h>
#include <unistd.h>

void	execut_cd(t_cmd_tab cmd)
{
	(void)cmd;
	printf("nothing yet\n");
	return ;
}

void	execut_pwd(t_cmd_tab cmd)
{
	pid_t	pid;
	char	cwd[128];

	(void)cmd;
	pid = fork();
	if (pid == 0)
	{
		getcwd(cwd, 128);
		printf("%s\n", cwd);
	}
	waitpid(pid, NULL, 0);
}

void	execut_she(t_cmd_tab cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd.env, cmd.cmd, env) == -1)
			perror("execve");
	}
	waitpid(pid, NULL, 0);
}

void	ft_exit(t_cmd_tab cmd)
{
	int	num;

	num = 0;
	if (cmd.cmd[1] != NULL)
	{
		num = ft_atoi(cmd.cmd[1]);
		if (cmd.cmd[2] != NULL)
		{
			ft_printf("too many arguments\n");
			return ;
		}
	}
	exit(num);
}

void	builtins(t_cmd_tab cmd, char **env)
{
	if (ft_strncmp(cmd.cmd[0], "cd", ft_strlen(cmd.cmd[0])) == 0)
		execut_cd(cmd);
	else if (ft_strncmp(cmd.cmd[0], "pwd", ft_strlen(cmd.cmd[0])) == 0)
		execut_pwd(cmd);
	else if (ft_strncmp(cmd.cmd[0], "exit", ft_strlen(cmd.cmd[0])) == 0)
		ft_exit(cmd);
	else
		execut_she(cmd, env);
}
