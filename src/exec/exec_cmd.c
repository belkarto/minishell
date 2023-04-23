/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:46:29 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/22 22:33:04 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>
#include <sys/fcntl.h>
#include <unistd.h>

// 0 read end of pip
// 1 write end of pip 

void	open_pipes(t_pipe fd_pip, int ind)
{
	if (ind == 0)
	{
		pipe(fd_pip.read_end);
		pipe(fd_pip.write_end);
	}
	else
		pipe(fd_pip.write_end);
}

void	set_pipes(t_pipe *pip, int i, int fd_pip[2][2])
{
	if (i % 2 == 0)
	{
		pip->read_end = fd_pip[0];
		pip->write_end = fd_pip[1];
	}
	else
	{
		pip->read_end = fd_pip[1];
		pip->write_end = fd_pip[0];
	}
}

pid_t	*allocat_pid_tab(t_cmd_tab *cmd_tab)
{
	pid_t	*pid;

	if (cmd_tab == NULL)
		return (NULL);
	pid = ft_calloc(cmd_tab->len, sizeof(int));
	if (!pid)
		return (NULL);
	return (pid);
}

void	exec_multi_cmd(pid_t *pid, t_cmd_tab *cmd_tab)
{
	t_pipe	pip;
	int		fd_pip[2][2];
	int		i;

	i = -1;
	while (++i < cmd_tab->len)
	{
		set_pipes(&pip, i, fd_pip);
		open_pipes(pip, i);
		pid[i] = exec_cmd(cmd_tab[i], pip, cmd_tab->len, i);
		close(pip.read_end[0]);
		close(pip.read_end[1]);
	}
	close(pip.write_end[0]);
	close(pip.write_end[1]);
}

pid_t	*exec_cmd_tab(t_cmd_tab *cmd_tab)
{
	int		i;
	pid_t	*pid;

	if (open_heredoc(cmd_tab) == 1)
		return (NULL);
	i = -1;
	pid = allocat_pid_tab(cmd_tab);
	if (!pid)
		return (NULL);
	if (cmd_tab->len == 1)
		pid[0] = exec_one(*cmd_tab);
	else
		exec_multi_cmd(pid, cmd_tab);
	return (pid);
}
