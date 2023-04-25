/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 05:55:35 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 15:51:09 by belkarto         ###   ########.fr       */
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
	if (env[i] == '\0' && env[i - 1] == '+')
		return (NULL);
	return (ft_substr(env, 0, i));
}

t_env	*builtin_env(void)
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

void	add_new_var(char *name, char *content)
{
	char	*env;

	env = ft_strjoin(name, "=");
	env = ft_strjoin_gnl(env, content);
	free(name);
	free(content);
	env_add_back(&g_meta.env, new_env(env));
	free(env);
}

static int	env_len(void)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = g_meta.env;
	while(tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	update_env(void)
{
	int		len;
	char	**updated_env;
	t_env	*tmp;
	int		i;

	i = 0;
	len = env_len();
	updated_env = ft_calloc(len + 1, sizeof(char *));
	if (!updated_env)
		return ;
	free_2d(g_meta.exec_env);
	tmp = g_meta.env;
	while(tmp)
	{
		if (updated_env[i])
		{
			updated_env[i] = ft_strdup(tmp->name);
			updated_env[i] = ft_strjoin_gnl(updated_env[i], "=");
			updated_env[i] = ft_strjoin_gnl(updated_env[i], tmp->content);
		}
		i++;
		tmp = tmp->next;
	}
	g_meta.exec_env = updated_env;
}
