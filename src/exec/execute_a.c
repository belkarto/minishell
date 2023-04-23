/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:38:22 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 08:44:53 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	put_error(char *error, bool state)
{
	if (error == NULL)
		ft_putstr_fd(strerror(errno), 2);
	else
	{
		ft_putstr_fd("ERROR : ", 2);
		ft_putstr_fd(error, 2);
	}
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

int	open_files(t_redir *files)
{
	t_redir	*tmp;
	int		check;

	if (files == NULL)
		return (0);
	tmp = files;
	while (tmp)
	{
		if (tmp->redir_type == LESS || tmp->redir_type == HEREDOC)
			check = open_in_file(*tmp);
		else if (tmp->redir_type == GREAT || tmp->redir_type == REDIR_OUT)
			check = open_out_file(*tmp);
		if (check == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	executor(t_cmd_tab cmd, t_pipe fd_pipe, t_phase phase)
{
	ft_dup(fd_pipe, phase);
	open_files(cmd.redir);
	if (cmd.cmd == NULL || cmd.cmd[0][0] == 0)
		exit (0);
	if (cmd.env == NULL)
		put_error(cmd.cmd[0], true);
	builtins(cmd, true);
	if (execve(cmd.env, cmd.cmd, g_meta.exec_env) == -1)
		put_error(NULL, true);
}

int	exec_cmd(t_cmd_tab cmd, t_pipe fd_pipe, int len, int ind)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		put_error("fork", false);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		cmd.env = generate_cmd_env(cmd.cmd[0]);
		if (ind == 0)
			executor(cmd, fd_pipe, FIRST);
		else if (ind == len - 1)
			executor(cmd, fd_pipe, LAST);
		else
			executor(cmd, fd_pipe, MIDDLE);
	}
	return (pid);
}
