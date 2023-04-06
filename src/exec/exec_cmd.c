/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:46:29 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/06 06:27:09 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	i;
	int	pid;
	int	**pipes;

	if (cmd_tab->len == 0)
		return ;
	else
	{
		if (cmd_tab->len > 1)
		{
			i = -1;
			pipes = ft_calloc(cmd_tab->len - 1, sizeof(int *));
			while (++i < cmd_tab->len)
				pipes[i] = ft_calloc(2, sizeof(int));
		}
	}
}
