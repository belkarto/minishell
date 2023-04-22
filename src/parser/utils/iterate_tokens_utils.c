/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:31:27 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/22 15:29:40 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*inside_quotes(t_cmd_tab *cmd_tab, t_elem *token, int index)
{
	is_expand(token);
	token = delete_quotes(cmd_tab, token, index, token->type);
	return (token);
}

void	skip_spaces(t_elem **tokens)
{
	if (!(*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		return ;
	}
	(*tokens) = (*tokens)->next;
	delet_elem(&(*tokens)->prev);
	while ((*tokens))
	{
		if ((*tokens)->type != SPAC)
			return ;
		(*tokens) = (*tokens)->next;
	}
}

t_elem	*join_none_space(t_elem *tokens)
{
	while (tokens->next)
	{
		if (tokens->type != WORD || tokens->type == SPAC)
			break ;
		tokens->content
			= ft_strjoin_gnl(tokens->content, tokens->next->content);
		tokens = tokens->next;
	}
	return (tokens);
}
