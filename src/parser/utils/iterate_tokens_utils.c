/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:31:27 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/23 05:04:46 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*inside_quotes(t_cmd_tab *cmd_tab, t_elem *token)
{
	is_expand(token, token->type);
	token = delete_quotes(cmd_tab, token, token->type);
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
