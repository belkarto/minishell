/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:33:02 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/15 08:51:36 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
#include <stdio.h>

t_env	*new_env(char *env)
{
	char	**tmp;
	t_env	*new;

	tmp = ft_split(env, '=');
	new = ft_calloc(1, sizeof(t_env));
	new->name = tmp[0];
	new->content = tmp[1];
	new->next = NULL;
	free(tmp);
	return (new);;
}

void	env_add_back(t_env **list, t_env *new)
{
	t_env	*tmp;

	tmp = *list;
	if (tmp == NULL)
	{
		(*list) = new;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
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

	len = d_strlen(env);
	i = -1;
	while (++i < len)
		env_add_back(&list, new_env(env[i]));
	return (list);
}
