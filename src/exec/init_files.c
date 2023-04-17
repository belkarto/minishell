/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:00:50 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/17 20:35:36 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	open_out_file(t_redir files)
{
	int		out_file;

	out_file = -1;
	if (files.redir_type == GREAT)
	{
		out_file = open(files.file_name, O_WRONLY | O_CREAT, 0644);
	}
	else {
		out_file = open(files.file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (out_file == -1)
		put_error("open :", false);
	else
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}

}

void	open_in_file(t_redir files)
{
	int	in_file;

	in_file = -1;
	if (files.redir_type == LESS)
	{
		in_file = open(files.file_name, O_RDONLY);
		if (in_file == -1)
			put_error("open :", false);
		else
		{
			dup2(in_file, STDIN_FILENO);
			close(in_file);
		}
	}
	else
	{
	//herdoc open
	// open_heredoc();
	}
}
