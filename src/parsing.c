/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/06 03:01:13 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"
#include <stdlib.h>


void	parsing_input(char *input)
{
	t_elem	*head;

	if (input == NULL)
		end_of_file();
	head = lexer(input);
}