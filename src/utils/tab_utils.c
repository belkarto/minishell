/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:43:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/17 20:44:08 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	tab_len(t_elem *head)
{
	int		i;

	i = 1;
	while (head)
	{
		if (head->type == PIPE && head->state == GENERAL)
		{
			head = head->next;
			while (head && head->type == SPAC)
				head = head->next;
			i++;
		}
		head = head->next;
	}
	return (i);
}

void	cmd_tab_free(t_cmd_tab **cmd_tab)
{
	int	i;
	t_cmd_tab	*cmd;

	cmd = *cmd_tab;
	i = -1;
	while (++i < (*cmd_tab)->len)
	{
		clear_files(cmd[i].redir);
		free(cmd[i].env);
		free_2d(cmd[i].cmd);
	}
	free(cmd);
	(*cmd_tab) = NULL;

}
