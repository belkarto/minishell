/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:14:50 by brahim            #+#    #+#             */
/*   Updated: 2023/03/23 03:04:52 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int	env_len(t_env *head)
{
	int i;
	t_env	*tmp;

	i = 0;
	tmp = head;
	while (tmp != NULL) {
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_env **get_array(t_env *head)
{
	int		len;
	t_env	*tmp;

	tmp = head;
	len = env_len(head);
	t_env **arr = (t_env **)ft_calloc((len + 1), sizeof(t_env *));
	int i = 0;
	while (tmp != NULL)
	{
		arr[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (arr);
}

void	sorting(t_env **head)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = -1;
	while (head[++i])
	{
		j = i + 1;
		while (head[j])
		{
			if (ft_strcmp(head[i]->name, head[j]->name) > 0)
			{
				tmp = head[i];
				head[i] = head[j];
				head[j] = tmp;
			}
			j++;
		}
	}
}

void	sort_env(t_env *head)
{
	t_env	**arr;
	int		i;

	arr = get_array(head);
	sorting(arr);
	i = -1;
	while (arr[++i])
	{
		if (arr[i]->content == NULL)
			printf("declare -x %s\n", arr[i]->name);
		else
			printf("declare -x %s=\"%s\"\n", arr[i]->name, arr[i]->content);
	}
	free(arr);
}
