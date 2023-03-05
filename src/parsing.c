/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/05 16:43:34 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"
#include <stdlib.h>

t_elem	*new_elem(char *con, int len, int token, int state)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	elem->state = state;
	elem->type	= token;
	elem->len = len;
	elem->content = con;
	return (elem);
}

void	lexer(char *str)
{
	t_list	*head;
	t_state	state;

	state = GENERAL;

}

void	parsing_input(char *input)
{
	if (input == NULL)
		end_of_file();
	lexer(input);
}
