/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:01:18 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 11:55:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0 || ft_isdigit(name[0]) || name[0] == '+')
	{
		g_meta.exit_status = 1;
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if (name[i] == '+' && name[i + 1] == 0)
				return (0);
			ft_putstr_fd("not a valid identifier\n", 2);
			g_meta.exit_status = 1;
			free(name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_exist(char *name, char *env)
{
	t_env	*holder;
	int		start;

	start = ft_strlen(name) + 1;
	if (name[start - 2] == '+')
		return (join_env(name, env));
	holder = get_var(name, g_meta.env);
	if (holder != NULL)
	{
		if (ft_strrchr(env, '=') == NULL)
		{
			free(name);
			return (1);
		}
		free(holder->content);
		holder->content = ft_substr(env, start, ft_strlen(env) - start);
		free(name);
		return (1);
	}
	return (0);
}

static void	env_control(char *env)
{
	char	*name;

	name = get_name(env);
	if (check_name(name) == 1)
		return ;
	else
	{
		if (check_exist(name, env) == 1)
			return ;
		else
			env_add_back(&g_meta.env, new_env(env));
		free(name);
	}
}

void	ft_export(t_cmd_tab cmd, bool in_child)
{
	int		len;
	int		i;

	i = 0;
	g_meta.exit_status = 0;
	len = d_strlen(cmd.cmd);
	if (len == 1)
	{
		sort_env(g_meta.env);
		g_meta.exit_status = 0;
	}
	else if (len > 1)
	{
		while (++i < len)
			env_control(cmd.cmd[i]);
	}
	if (in_child == true)
		exit(0);
}
