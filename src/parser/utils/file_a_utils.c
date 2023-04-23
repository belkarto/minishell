/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_a_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:23:06 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/22 23:43:04 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redir	*file_new(char *file_name, t_token redir_type, bool in_quote)
{
	t_redir	*elem;

	elem = ft_calloc(sizeof(t_redir), 1);
	if (!elem)
		return (NULL);
	if (redir_type == HEREDOC)
		g_meta.heredoc++;
	elem->file_name = ft_strdup(file_name);
	elem->redir_type = redir_type;
	elem->in_quote = in_quote;
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

t_elem	*delete_file(t_elem *token)
{
	if (!token)
		return (NULL);
	if (token->next)
	{
		token = token->next;
		delet_elem(&token->prev);
		token = token->prev;
	}
	else
	{
		token = token->prev;
		delet_elem(&token->next);
	}
	return (token);
}

void	clear_files(t_redir *list)
{
	t_redir	*tmp;

	tmp = list;
	while (tmp)
	{
		list = list->next;
		free(tmp->file_name);
		free(tmp);
		tmp = list;
	}
	list = NULL;
}
