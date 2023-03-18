/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 05:55:35 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/18 08:40:22 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	del_var(t_env *var)
{
	free(var->name);
	free(var->content);
	free(var);
}

char	*get_name(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

t_env	*builtin_env()
{
	t_env	*tmp;
	t_env	*head;

	tmp = ft_calloc(1, sizeof(t_env));
	head = tmp;
	tmp->name = ft_strdup("OLDPWD");
	tmp->content = NULL;
	tmp->next = ft_calloc(1, sizeof(t_env));
	tmp = tmp->next;
	tmp->name = ft_strdup("PWD");
	tmp->content = ft_calloc(255, sizeof(char));
	getcwd(tmp->content, 128);
	tmp->next = ft_calloc(1, sizeof(t_env));
	tmp = tmp->next;
	tmp->name = ft_strdup("SHLVL");
	tmp->content = ft_strdup("1");
	tmp->next = NULL;
	return (head);
}
