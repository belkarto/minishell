/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:01:18 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/17 05:10:02 by belkarto         ###   ########.fr       */
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

char	*get_name(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

int	check_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0 || ft_isdigit(name[0]))
	{
		g_meta.ex_statu = 1;
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
			g_meta.ex_statu = 1;
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
	int		name_len;

	name_len = ft_strlen(name);
	start = ft_strlen(name) + 1;
	if (name[start - 2] == '+')
	{
		return (join_env(name, env));
	}
	holder = g_meta.env;
	while (holder)
	{
		if (ft_strncmp(name, holder->name, name_len) == 0)
		{
			free(holder->content);
			holder->content = ft_substr(env, start, ft_strlen(env) - start);
			free(name);
			return (1);
		}
		holder = holder->next;
	}
	return (0);
}

void	env_control(char *env)
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

void	ft_export(t_cmd_tab cmd)
{
	int		len;
	int		i;

	i = 0;
	g_meta.ex_statu = 0;
	len = d_strlen(cmd.cmd);
	if (len == 1)
	{
		ft_print_env();
		g_meta.ex_statu = 0;
		return ;
	}
	else if (len > 1)
	{
		while (++i < len)
		{
			env_control(cmd.cmd[i]);
		}
	}
	return ;
}
