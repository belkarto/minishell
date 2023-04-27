/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:43:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 04:45:45 by ohalim           ###   ########.fr       */
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

void	cmd_tab_free(t_cmd_tab **cmd_tab, int len)
{
	int			i;
	t_cmd_tab	*cmd;

	cmd = *cmd_tab;
	i = 0;
	if (cmd == NULL)
		return ;
	while (i <= len)
	{
		if (cmd[i].redir)
			clear_files(cmd[i].redir);
		if (cmd[i].env)
			free(cmd[i].env);
		if (cmd[i].cmd)
			free_2d(cmd[i].cmd);
		i++;
	}
	free(cmd->syntax_error);
	free((*cmd_tab));
	(*cmd_tab) = NULL;
}
