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
	return (elem);
}

void	elem_add_tail(t_elem **elem, t_elem *new_elem)
{

	if ((*elem) == NULL)
	{
		(*elem) = new_elem;
		(*elem)->tail = new_elem;
		(*elem)->head = new_elem;
		(*elem)->next = NULL;
	}
	else
	{
		(*elem)->tail->next = new_elem;
		new_elem->next = NULL;
		(*elem)->tail = new_elem;
	}
}
