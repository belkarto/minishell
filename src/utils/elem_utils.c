/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:30:48 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/08 23:36:02 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_elem	*new_elem(char *con, int len, int token, int state)
{
	t_elem	*elem;

	elem = ft_calloc(sizeof(t_elem), 1);
	if (!elem)
		return (NULL);
	elem->state = state;
	elem->type	= token;
	elem->len = len;
	elem->content = con;
	elem->next = NULL;
	// printf("%s\n", elem->content);
	return (elem);
}

void	elem_add_tail(t_elem **elem, t_elem *new_elem)
{
	t_elem	*tmp;

	tmp = (*elem);
	if (tmp == NULL)
	{
		tmp = new_elem;
		tmp->tail = new_elem;
		tmp->head = new_elem;
		tmp->next = NULL;
	}
	else
	{
		tmp->tail->next = new_elem;
		new_elem->next = NULL;
		tmp->tail = new_elem;
	}
}
