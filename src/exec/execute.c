/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:38:22 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/19 05:57:05 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/types.h>
#include <unistd.h>

void	put_error(char *error, bool state)
{
	ft_putstr_fd("ERROR : ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(" :\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (state == true)
		exit(127);
	else
		return ;
}

void	ft_dup(t_pipe fd_pipe, t_phase phase)
{
	if (phase == FIRST)
		dup2(fd_pipe.write_end[1], STDOUT_FILENO);
	else if (phase == MIDDLE)
	{
		dup2(fd_pipe.read_end[0], STDIN_FILENO);
		dup2(fd_pipe.write_end[1], STDOUT_FILENO);
	}
	else if (phase == LAST)
	{
		dup2(fd_pipe.read_end[0], STDIN_FILENO);
	}
	close(fd_pipe.read_end[0]);
	close(fd_pipe.read_end[1]);
	close(fd_pipe.write_end[0]);
	close(fd_pipe.write_end[1]);
}

void	open_files(t_redir *files)
{
	t_redir *tmp;

	if (files == NULL)
		return ;
	tmp = files;
	while (tmp)
	{
		if (tmp->redir_type == LESS || tmp->redir_type == HEREDOC)
			open_in_file(*tmp);
		else if (tmp->redir_type == GREAT || tmp->redir_type == REDIR_OUT)
			open_out_file(*tmp);
		tmp = tmp->next;
	}
}

void	executor(t_cmd_tab cmd, t_pipe fd_pipe, t_phase phase, char **env)
{
	ft_dup(fd_pipe, phase);
	open_files(cmd.redir);
	if (cmd.cmd == NULL)
		exit (127);
	builtins(cmd, true);
	if (execve(cmd.env, cmd.cmd, env) == -1)
		put_error("ERROR : exeve", true);
}

int	exec_cmd(t_cmd_tab cmd, t_pipe fd_pipe, int len, int ind, char **env)
{
	pid_t	pid;
	if ((pid = fork()) < 0)
		put_error("fork", true);
	if (pid == 0)
	{
		if (ind == 0)
			executor(cmd, fd_pipe, FIRST, env);
		else if (ind == len - 1)
			executor(cmd, fd_pipe, LAST, env);
		else
			executor(cmd, fd_pipe, MIDDLE, env);
	}
	return (pid);
}

pid_t	exec_one(t_cmd_tab cmd, char **env)
{
	pid_t	pid;

	pid = -1;
	if (cmd.cmd != NULL && is_builtin(cmd.cmd[0]))
	{
		open_files(cmd.redir);
		builtins(cmd, false);
	}
	else
	{
		if ((pid = fork()) < 0)
			put_error("fork :", true);
		if (pid == 0)
		{
			open_files(cmd.redir);
			if (cmd.cmd == NULL)
				exit(127);
			if (execve(cmd.env, cmd.cmd, env) == -1)
			{
				put_error("ERROR : exeve", true);
			}
		}
	}
	return (pid);
}
