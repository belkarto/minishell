/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:52:34 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/21 15:58:12 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_builtin(char *content)
{
	if (!content)
		return (0);
	return ((ft_strcmp(content, "echo") == 0)
		|| (ft_strcmp(content, "cd") == 0)
		|| (ft_strcmp(content, "pwd") == 0)
		|| (ft_strcmp(content, "export") == 0)
		|| (ft_strcmp(content, "unset") == 0)
		|| (ft_strcmp(content, "env") == 0)
		|| (ft_strcmp(content, "exit") == 0));
}

static char	*generate_paths(void)
{
	t_env	*env;

	env = g_meta.env;
	while (env)
	{
		if (ft_strncmp("PATH", env->name, 4) == 0)
			return (env->content);
		env = env->next;
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
	path = (char **)ft_calloc(i + 1, sizeof(char **));
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
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = generate_paths();
	if (!paths)
		return (NULL);
	path = split_add_slash(paths);
	if (!paths)
		return (NULL);
	while (path[++i])
	{
		env = ft_strjoin(path[i], cmd);
		if (access(env, X_OK) == 0)
		{
			free_2d(path);
			return (env);
		}
		free (env);
	}
	free_2d(path);
	return (NULL);
}
