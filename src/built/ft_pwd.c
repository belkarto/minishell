/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:54:34 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/18 05:34:09 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	ft_pwd(t_cmd_tab cmd, bool in_child)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 128);
	if (cwd)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	free(cwd);
	if (in_child == true)
		exit (0);
}
