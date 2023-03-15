/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:01:18 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/15 11:27:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_env(void)
{
	t_env	*tmp;

	tmp = g_meta.env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	ft_export(t_cmd_tab cmd)
{
	if (cmd.cmd[1] == NULL)
	{
		ft_print_env();
		g_meta.ex_statu = 0;
		return ;
	}
}
