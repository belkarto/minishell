/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:57:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/21 16:38:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	update_var_oldpwd(char *cwd)
{
	t_env	*var;

	var = get_var("OLDPWD", g_meta.env);
	if (var != NULL && cwd != NULL)
	{
		free(var->content);
		var->content = ft_strdup(cwd);
	}
	free (cwd);
}

static void	update_pwd(void)
{
	t_env	*var;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	var = get_var("PWD", g_meta.env);
	if (var != NULL && cwd != NULL)
	{
		free(var->content);
		var->content = ft_strdup(cwd);
	}
	free (cwd);
}

static	char	*get_home(void)
{
	t_env	*var;
	var = get_var("HOME", g_meta.env);
	if (var != NULL)
		return (ft_strdup(var->content));
	else
		ft_putstr_fd("cd : HOME not set\n", 2);
	return (NULL);
}

void	ft_cd(t_cmd_tab cmd, bool in_child)
{
	char	*dir;
	char	*pwd;

	if (cmd.cmd[1] == NULL)
	{
		dir = get_home();
	}
	else
		dir = ft_strdup(cmd.cmd[1]);
	pwd = getcwd(NULL, 0);
	if (chdir(dir) == 0)
	{
		update_var_oldpwd(pwd);
		update_pwd();
	}
	else
	{
		free(pwd);
		put_error(NULL, false);
	}
	free(dir);
	if (in_child == true)
		exit(0);
	return ;
}
