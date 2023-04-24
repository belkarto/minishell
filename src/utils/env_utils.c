/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:33:02 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 11:30:39 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *env)
{
	t_env	*new;
	int		len;
	int		start;
	char	*tmp;

	new = ft_calloc(1, sizeof(t_env));
	tmp = ft_strchr(env, '=');
	if (tmp == NULL)
		new->content = NULL;
	else
	{
		start = tmp - env + 1;
		len = ft_strlen(env) - (ft_strchr(env, '=') - env);
		new->content = ft_substr(env, start, len);
	}
	new->name = ft_substr(env, 0, tmp - env);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **list, t_env *new_env)
{
	t_env	*tmp;

	tmp = *list;
	if (tmp == NULL)
	{
		(*list) = new_env;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

int	d_strlen(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	add_new_var(char *name, char *content)
{
	char	*env;

	env = ft_strjoin(name, "=");
	env = ft_strjoin_gnl(env, content);
	free(name);
	free(content);
	ft_printf("%s\n", env);
	env_add_back(&g_meta.env, new_env(env));
}

int	join_env(char *name, char *env)
{
	t_env	*tmp;
	char	*new_name;
	char	*join;

	tmp = g_meta.env;
	new_name = ft_strtrim(name, "+");
	free(name);
	name = new_name;
	join = ft_substr(env, ft_strlen(name) + 2, ft_strlen(env));
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			tmp->content = ft_strjoin_gnl(tmp->content, join);
			free(join);
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	add_new_var(name, join);
	return (1);
}

t_env	*init_env(char **env)
{
	t_env	*list;
	int		len;
	int		i;

	list = NULL;
	len = d_strlen(env);
	i = -1;
	while (++i < len)
		env_add_back(&list, new_env(env[i]));
	if (list == NULL)
		return (builtin_env());
	else
		shell_lvl(list);
	return (list);
}
