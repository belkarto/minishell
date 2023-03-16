/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:01:18 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/16 19:21:12 by belkarto         ###   ########.fr       */
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
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
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

	if (ft_strlen(name) == 0)
	{
		ft_putstr_fd("bad assigment\n", 2);
		free(name);
		return (1);
	}
	start = ft_strlen(name) + 1;
	holder = g_meta.env;
	while (holder)
	{
		if (ft_strncmp(name, holder->name, ft_strlen(name)) == 0)
		{
			free(holder->content);
			holder->content = ft_substr(env, start, ft_strlen(env) - start);
			free(name);
			return (1);;
		}
	}
	return (0);
}

void	env_control(char *env)
{
	char	*name;

	name = get_name(env);
	if (check_exist(name, env) == 1)
		return ;
	else
	{
		if (check_name(name) == 1)
			return ;
		else
			env_add_back(&g_meta.env, new_env(env));
		free(name);
	}
}

void	ft_export(t_cmd_tab cmd)
{
	int		len;

	len = d_strlen(cmd.cmd);
	if (len == 1)
	{
		ft_print_env();
		g_meta.ex_statu = 0;
		return ;
	}
	else if (len == 2)
	{
		env_control(cmd.cmd[1]);
	}
	return ;
}
