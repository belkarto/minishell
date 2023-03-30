/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:23:06 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/30 20:44:34 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

t_redir	*file_new(char *file_name, t_token redir_type)
{
	t_redir	*elem;

	elem = ft_calloc(sizeof(t_redir), 1);
	if (!elem)
		return (NULL);
	elem->file_name = ft_strdup(file_name);
	elem->redir_type = redir_type;
	elem->next = NULL;
	return (elem);
}

void	file_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
