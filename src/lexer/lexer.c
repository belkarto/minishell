/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/22 23:44:15 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

t_elem	*lexer(char *line)
{
	int		i;
	int		statu;
	t_elem	*head;

	g_meta.heredoc = 0;
	head = new_elem(NULL, 0, WORD, GENERAL);
	statu = GENERAL;
	i = 0;
	while (line[i])
		i += token(&head, &statu, line + i);
	return (head);
}
