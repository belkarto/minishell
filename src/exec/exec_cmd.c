/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:46:29 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/06 16:50:54 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

// 0 read end of pip
// 1 write end of pip 
int	**open_pipes(int len)
{
	int	**pipes;
	int	i;

	if (len == 0)
		return (NULL);
	else
	{
		if (len > 1)
		{
			i = -1;
			pipes = ft_calloc(len - 1, sizeof(int *));
			while (++i < len - 1)
			{
				pipes[i] = ft_calloc(2, sizeof(int));
				if (pipe(pipes[i]) == -1)
					break ;
			}
		}
	}
	return (pipes);
}

void	iterate_cmds(t_cmd_tab cmd, int **pip, int index)
{
}

void	execute_cmds(t_cmd_tab *cmds, int **pip_line)
{
	int	i;

	i = -1;
	while (++i)
	{
		iterate_cmds(cmds[i], pip_line, i);
	}
}

void	exec_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	**pipes;

	pipes = open_pipes(cmd_tab->len);
	execute_cmds(cmd_tab, pipes);
}
