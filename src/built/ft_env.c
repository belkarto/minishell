/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 05:59:10 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/06 00:59:51 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_cmd_tab cmd)
{
	t_env	*tmp;

	(void)cmd;
	tmp = g_meta.env;
	while (tmp)
	{
		if (tmp->content != NULL)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}
