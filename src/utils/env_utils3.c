/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:15:02 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/25 14:53:28 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**dup_env(char **env)
{
	int		len;
	char	**dup_env;
	int		i;

	i = -1;
	len = d_strlen(env);
	dup_env = ft_calloc(sizeof(char *), len + 1);
	if (!dup_env)
		return (NULL);
	while (env[++i])
		dup_env[i] = ft_strdup(env[i]);
	return (dup_env);
}

static int	env_len(void)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = g_meta.env;
	while (tmp)
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
	while (tmp)
	{
			updated_env[i] = ft_strdup(tmp->name);
			updated_env[i] = ft_strjoin_gnl(updated_env[i], "=");
			updated_env[i] = ft_strjoin_gnl(updated_env[i], tmp->content);
		i++;
		tmp = tmp->next;
	}
	g_meta.exec_env = updated_env;
}
