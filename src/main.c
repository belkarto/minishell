/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/02/22 17:26:27 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	ft_putstr_fd("test\n", 1);
	return EXIT_SUCCESS;
}
