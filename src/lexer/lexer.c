/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/23 03:43:34 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

t_elem	*lexer(char *line)
{
	int		i;
	int		statu;
	t_elem	*head;

	head = NULL;
	statu = GENERAL;
	i = 0;
	while (line[i])
		i += token(&head, &statu, line + i);
	return (head);
}
