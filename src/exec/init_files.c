/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:00:50 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/22 23:53:38 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/fcntl.h>
#include <sys/signal.h>
#include <unistd.h>

int	open_heredoc(t_cmd_tab *cmd_tab)
{
	int	i;
	t_redir	*file;

	if (g_meta.heredoc >= MAX_HERDOC)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		exit (2);
	}
	i = -1;
	while (++i < cmd_tab->len && g_meta.heredoc > 0)
	{
		file = cmd_tab->redir;
		while (file)
		{
			if (file->redir_type == HEREDOC)
			{
				if (heredoc_content(file) == 1)
					return (1);
			}
			file = file->next;
		}
	}
	return (0);
}

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

int	open_in_file(t_redir files)
{
	int	in_file;
	int	fd_pipe[2];

	in_file = -1;
	if (files.redir_type == LESS)
		in_file = open(files.file_name, O_RDONLY);
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
