/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:01:18 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/18 05:36:28 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	ft_echo(t_cmd_tab cmd, bool in_child)
{
	int	i;
	int	j;
	char	*str;
	bool	print_line;

	print_line = true;
	i = 0;
	if (cmd.cmd[1] && ft_strcmp(cmd.cmd[1], "-n") == 0)
	{
		i++;
		print_line = false;
	}
	while (cmd.cmd[++i])
	{
		j = -1;
		str = cmd.cmd[i];
		while (str[++j])
			write(1, &str[j], 1);
		write(1, " ", 1);
	}
	if (print_line == true)
		write(1, "\n", 1);
	if (in_child == true)
		exit(0);
}
