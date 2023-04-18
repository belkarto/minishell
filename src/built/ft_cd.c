/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:57:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/18 04:43:18 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_cd(t_cmd_tab cmd, bool in_child)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*tmp;

	chdir(cmd.cmd[1]);
	tmp = getcwd(NULL, 255);
	pwd = get_var("PWD", g_meta.env);
	if (pwd && ft_strcmp(pwd->content, tmp) == 0)
		return ;
	else
	{
		old_pwd = get_var("OLDPWD", g_meta.env);
		if (old_pwd)
		{
			free(old_pwd->content);
			old_pwd->content = pwd->content;
		}
		if (pwd)
			pwd->content = ft_strdup(tmp);
	}
	if (in_child == true)
		exit(0);
	return ;
}
