/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:00:50 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/21 10:56:13 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/fcntl.h>
#include <sys/signal.h>
#include <unistd.h>

int	open_out_file(t_redir files)
{
	int		out_file;

	out_file = -1;
	if (files.redir_type == GREAT)
		out_file = open(files.file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		out_file = open(files.file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_file == -1)
	{
		put_error(NULL, false);
		return (-1);
	}
	else
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	return (-1);

}


void	quitin(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(0);
}

void	open_heredocs(char *delemiter)
{
	int	fd_pipe[2];
	char	*line;

	pipe(fd_pipe);
	signal(SIGINT, quitin);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(delemiter, line) == 0)
		{
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			return ;
		}
		else
			write(fd_pipe[0], line, ft_strlen(line));
	}
}

int	open_in_file(t_redir files)
{
	int	in_file;
	int	fd_pipe[2];

	in_file = -1;
	if (files.redir_type == LESS)
		in_file = open(files.file_name, O_RDONLY | O_TRUNC);
	else
	{
		pipe(fd_pipe);
		ft_putstr_fd(files.file_name, fd_pipe[1]);
		in_file = fd_pipe[0];
		close(fd_pipe[1]);
	}
	if (in_file == -1)
	{
		put_error(NULL, false);
		return (-1);
	}
	else
	{
		dup2(in_file, STDIN_FILENO);
		close(in_file);
	}
	return (0);
}

