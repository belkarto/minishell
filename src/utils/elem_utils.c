/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:30:48 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/10 04:55:27 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_elem	*new_elem(char *con, int len, int token, int state)
{
	t_elem	*elem;

	elem = ft_calloc(sizeof(t_elem), 1);
	if (!elem)
		return (NULL);
	elem->content = con;
	elem->len = len;
	elem->type = token;
	elem->state = state;
	elem->next = NULL;
	elem->tail = NULL;
	elem->prev = NULL;
	return (elem);
}

void	elem_clear(t_elem *list)
{
	t_elem	*tmp_a;
	t_elem	*tmp_b;

	tmp_a = list;
	while (tmp_a)
	{
		tmp_b = tmp_a->next;
		free(tmp_a->content);
		free(tmp_a);
		tmp_a = tmp_b;
	}
	list = NULL;
}

void	delete_elem(t_elem	**elem)
{
	t_elem	*tmp;

	tmp = *elem;
	if ((*elem)->prev == NULL)
	{
		(*elem)->head = (*elem)->next;
		if ((*elem)->next != NULL)
			(*elem)->next->prev = NULL;
	}
	else if ((*elem)->next == NULL)
	{
		(*elem)->tail = (*elem)->prev;
		if ((*elem)->prev != NULL)
			(*elem)->prev->next = NULL;
	}
	else
	{

		(*elem)->prev->next = (*elem)->next;
		(*elem)->next->prev = (*elem)->prev;
	}
	free(tmp->content);
	free(tmp);
}
