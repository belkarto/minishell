/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:54:34 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/15 11:25:31 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_cmd_tab cmd)
{
	pid_t	pid;
	char	cwd[128];

	(void)cmd;
	pid = fork();
	if (pid == 0)
	{
		getcwd(cwd, 128);
		printf("%s\n", cwd);
		exit (0);
	}
	waitpid(pid, &g_meta.ex_statu, 0);
}
