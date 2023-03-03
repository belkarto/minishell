/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/03 22:53:40 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	init_program()
{
    /* printf("******************"
        "************************");
    printf("\n\t      ****MY SHELL****");
    printf("\n\t  -USE AT YOUR OWN RISK-");
    printf("\n*******************"
        "***********************\n"); */
}



int main()
{
	char *readed;

	init_program();
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
