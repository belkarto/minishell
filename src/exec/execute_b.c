/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:49:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/24 06:43:36 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

int	run_builtin(t_cmd_tab cmd)
{
	if (cmd.cmd != NULL && is_builtin(cmd.cmd[0]))
	{
		open_files(cmd.redir);
		builtins(cmd, false);
		dup2(g_meta.fd_stdin, STDIN_FILENO);
		dup2(g_meta.fd_stdout, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

pid_t	run_external(t_cmd_tab cmd)
{
	pid_t	pid;

	pid = -1;
	pid = fork();
	if (pid < 0)
		put_error("fork:", false);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (open_files(cmd.redir) == -1)
			exit(1);
		cmd.env = generate_cmd_env(cmd.cmd[0]);
		if (cmd.cmd == NULL || cmd.cmd[0][0] == '\0')
			exit(0);
		if (cmd.env == NULL)
			put_error("command not found", true);
		if (execve(cmd.env, cmd.cmd, g_meta.exec_env) == -1)
			put_error("command not found", true);
	}
	return (pid);
}

pid_t	exec_one(t_cmd_tab cmd)
{
	pid_t	pid;

	pid = -1;
	if (run_builtin(cmd) == 1)
		return (-1);
	pid = run_external(cmd);
	return (pid);
}
