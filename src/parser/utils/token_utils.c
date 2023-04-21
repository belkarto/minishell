/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:50:32 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/21 16:25:59 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*join_tokens(t_elem **token, t_elem **next_token)
{
	if ((*token) == (*next_token))
		return (*token);
	if (!(*next_token))
		return ((*token));
	(*token)->content
		= ft_strjoin_gnl((*token)->content, (*next_token)->content);
	if ((*next_token)->next)
		(*token) = (*next_token)->next;
	else
	{
		delet_elem(&(*next_token));
		return ((*token));
	}
	if ((*token)->prev)
		delet_elem(&(*token)->prev);
	return ((*token)->prev);
}

void	join_unseparated_tokens(t_elem *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD && tokens->next && tokens->next->type == WORD)
			tokens = join_tokens(&tokens, &tokens->next);
		else
		{
			if (tokens->next)
				tokens = tokens->next;
			else
				break ;
		}
	}
}

void	delete_space(t_elem **tokens)
{
	t_elem	*tmp;
	t_elem	*head;

	head = (*tokens);
	while (head)
	{
		tmp = head->next;
		if (head->type == SPAC)
			delet_elem(&head);
		head = tmp;
	}
}

t_elem	*delete_token(t_elem *token)
{
	if (token->next)
	{
		token = token->next;
		delet_elem(&token->prev);
	}
	else
	{
		token = token->prev;
		delet_elem(&token->next);
	}
	return (token);
}
