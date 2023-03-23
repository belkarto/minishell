/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:57:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/23 00:57:41 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_cd(t_cmd_tab cmd)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	tmp1[255];

	chdir(cmd.cmd[1]);
	getcwd(tmp1, 255);
	pwd = get_var("PWD", g_meta.env);
	if (ft_strcmp(pwd->content, tmp1) == 0)
		return ;
	else
	{
		old_pwd = get_var("OLDPWD", g_meta.env);
		free(old_pwd->content);
		old_pwd->content = pwd->content;
		pwd->content = ft_strdup(tmp1);
	}
	return ;
}
