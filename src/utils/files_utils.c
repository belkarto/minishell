/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:36:19 by brahim            #+#    #+#             */
/*   Updated: 2023/03/26 03:48:32 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_file	*new_file(char *name, t_token type)
{
	t_file	*new;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (NULL);
	new->f_name = ft_strdup(name);
	new->type = type;
	new->next = NULL;
	return (new);
}

void	file_add_back(t_file **list, t_file *new_file)
{
	t_file	*tmp;

	tmp	= *list;
	if (tmp == NULL)
	{
		(*list) = new_file;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_file;
	}
}
