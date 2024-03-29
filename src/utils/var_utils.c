/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:19:31 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/25 14:59:40 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_var(char *name, t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	shell_lvl(t_env *list)
{
	t_env	*tmp;
	int		num;

	tmp = get_var("SHLVL", list);
	num = ft_atoi(tmp->content);
	num++;
	free(tmp->content);
	tmp->content = ft_itoa(num);
	tmp = get_var("OLDPWD", list);
	if (tmp)
	{
		free(tmp->content);
		tmp->content = NULL;
	}
}
