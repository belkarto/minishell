/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:19:31 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/18 08:52:52 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_var(char *name, t_env *list)
{
	t_env	*tmp;
	size_t	len;

	len = ft_strlen(name);
	tmp = list;
	while (tmp)
	{
		if (len < ft_strlen(tmp->content))
			len = ft_strlen(tmp->content);
		if (ft_strncmp(tmp->name, name, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	shell_lvl(t_env *list)
{
	t_env	*tmp;
	int	num;

	tmp = get_var("SHLVL", list);
	num = ft_atoi(tmp->content);
	num++;
	free(tmp->content);
	tmp->content = ft_itoa(num);
	tmp = get_var("OLDPWD", list);
	free(tmp->content);
	tmp->content = NULL;
}
