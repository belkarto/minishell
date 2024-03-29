/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 06:07:10 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/18 05:27:37 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

static int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0 || ft_isdigit(name[0]))
	{
		g_meta.exit_status = 1;
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			g_meta.exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	env_control(char *var)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = g_meta.env;
	if (check_name(var) == 1)
		return ;
	else
	{
		while (current)
		{
			if (ft_strcmp(var, current->name) == 0)
			{
				if (prev == NULL)
					g_meta.env = current->next;
				else
					prev->next = current->next;
				del_var(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
}

void	ft_unset(t_cmd_tab cmd, bool in_child)
{
	int	len;
	int	i;

	len = d_strlen(cmd.cmd);
	g_meta.exit_status = 0;
	i = 0;
	if (len > 1)
	{
		while (++i < len)
			env_control(cmd.cmd[i]);
	}
	if (in_child == true)
		exit(0);
}
