/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:57:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/20 12:20:43 by brahim           ###   ########.fr       */
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
	if (pwd && pwd->content &&  ft_strcmp(pwd->content, tmp) == 0)
		return ;
	else
	{
		old_pwd = get_var("OLDPWD", g_meta.env);
		if (old_pwd)
		{
			if (pwd)
			{
				free(old_pwd->content);
				old_pwd->content = pwd->content;
			}
			else
				old_pwd->content = getcwd(NULL, 255);
		}
		if (pwd)
			pwd->content = ft_strdup(tmp);
	}
	if (in_child == true)
		exit(0);
	return ;
}
