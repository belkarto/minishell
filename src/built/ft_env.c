/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 05:59:10 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/26 13:47:00 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdbool.h>

void	ft_env(t_cmd_tab cmd, bool in_child)
{
	t_env	*tmp;

	(void)cmd;
	tmp = g_meta.env;
	g_meta.exit_status = 0;
	while (tmp)
	{
		if (tmp->content != NULL)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	if (in_child == true)
		exit(0);
}
