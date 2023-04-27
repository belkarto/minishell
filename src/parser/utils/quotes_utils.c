/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:05:36 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/23 08:42:03 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*delete_last_quote(t_elem *token)
{
	if (token->next != NULL)
	{
		token = token->next;
		delet_elem(&(token->prev));
	}
	else
	{
		token = token->prev;
		delet_elem(&(token->next));
		return (token);
	}
	return (token->prev);
}

void	join_and_set_type(t_elem *tokens)
{
	tokens = join_tokens(&tokens, &tokens->next);
	tokens->type = WORD;
}

t_elem	*delete_quotes(t_cmd_tab *cmd_tab, t_elem *tokens, t_token redir_type)
{
	if (!tokens->next)
		return (error_unclosed_quotes(cmd_tab));
	tokens = tokens->next;
	delet_elem(&tokens->prev);
	while (tokens)
	{
		if (tokens->type != redir_type && tokens->next
			&& tokens->next->type != redir_type)
			join_and_set_type(tokens);
		else
		{
			if (tokens->type != redir_type && tokens->next)
			{
				tokens->type = WORD;
				tokens = tokens->next;
			}
			else if (!tokens->next)
				break ;
		}
		if (tokens->type == redir_type)
			break ;
	}
	if (!tokens->next && tokens->type != redir_type)
		return (error_unclosed_quotes(cmd_tab));
	return (delete_last_quote(tokens));
}

int	is_in_quote(t_elem *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->type == LESS
			|| tokens->type == GREAT || tokens->type == HEREDOC
			|| tokens->type == REDIR_OUT)
			break ;
		if (tokens->type == QUOTE || tokens->type == DQUOTE)
			i = 0;
		tokens = tokens->next;
	}
	return (i);
}
