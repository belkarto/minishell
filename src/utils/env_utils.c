/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:33:02 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/16 06:43:12 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
#include <stdio.h>

t_env	*new_env(char *env)
{
	t_env	*new;
	int		len;
	int		start;

	new = ft_calloc(1, sizeof(t_env));
	start = ft_strchr(env, '=') - env + 1;
	len = ft_strlen(env) - (ft_strchr(env, '=') - env);
	new->name = ft_substr(env, 0, ft_strchr(env, '=') - env);
	new->content = ft_substr(env, start, len);
	new->next = NULL;
	return (new);;
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
	return (list);
}
