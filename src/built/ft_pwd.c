/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:54:34 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/26 13:45:33 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	ft_pwd(t_cmd_tab cmd, bool in_child)
{
	char	cwd[MAX_SIZE];

	(void)cmd;
	g_meta.exit_status = 0;
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	if (in_child == true)
		exit (0);
}
