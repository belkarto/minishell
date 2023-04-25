/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:15:02 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 15:33:29 by belkarto         ###   ########.fr       */
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
	while(env[++i])
		dup_env[i] = ft_strdup(env[i]);
	return (dup_env);
}
