/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/07 21:43:32 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

t_elem	*lexer(char *line)
{
	int		i;
	int		statu;
	t_elem	*head;

	head = new_elem(NULL, 0, WORD, GENERAL);
	statu = GENERAL;
	i = 0;
	while (line[i])
		i += token(&head, &statu, line + i);
	if (head->tail->state != GENERAL)
	{
		ft_putstr_fd("syntax error\n", 2);
		elem_clear(head);
		g_meta.exit_status = 1;
		head = NULL;
	}
	return (head);
}
