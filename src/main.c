/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/02/28 22:36:21 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_program(int argc, char *argv[], char **env)
{
	if (argc != 1)
		exit (1);
	(void) argv;
	(void) env;
}



int main(int argc, char *argv[], char **env)
{
	char *readed;

	init_program(argc, argv, env);
	signals();
	while (1)
	{
		readed = readline("\033[0;1;3;32m MINISHELL $> \033[0;37m");
		if (readed && ft_strlen(readed))
			add_history(readed);
		parsing_input(readed);
		free(readed);
	}
	return (0);
}
