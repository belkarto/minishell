/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:52:34 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/18 05:52:38 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*generate_paths(void)
{
	t_env	*export;

	export = g_meta.env;
	while (export)
	{
		if (ft_strncmp("PATH", export->name, 4) == 0)
			return (export->content);
		export = export->next;
	}
	return (NULL);
}

static char	**split_add_slash(char *paths)
{
	int		i;
	char	**split;
	char	**path;

	i = 0;
	split = ft_split(paths, ':');
	while (split[i])
		i++;
	path = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!path)
		return (NULL);
	i = -1;
	while (split[++i])
		path[i] = ft_strjoin(split[i], "/");
	free_2d(split);
	return (path);
}

char	*generate_cmd_env(char *cmd)
{
	int		i;
	char	*env;
	char	*paths;
	char	**path;

	i = -1;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	if (!(paths = generate_paths()))
		return (NULL);
	if (!(path = split_add_slash(paths)))
		return (NULL);
	while (path[++i])
	{
		env = ft_strjoin(path[i], cmd);
		if (access(env, X_OK) != -1)
		{
			free_2d(path);
			return (env);
		}
		free (env);
	}
	free_2d(path);
	return (NULL);
}
