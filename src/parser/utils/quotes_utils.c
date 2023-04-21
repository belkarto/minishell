/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:05:36 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/21 16:25:00 by ohalim           ###   ########.fr       */
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

t_elem	*delete_quotes(t_cmd_tab *cmd_tab, t_elem *tokens, int index)
{
	t_token	type;

	type = tokens->type;
	if (tokens->next)
	{
		tokens = tokens->next;
		delet_elem(&tokens->prev);
	}
	else
	{
		delet_elem(&tokens);
		error_unclosed_quotes(cmd_tab, index);
		return (NULL);
	}
	while (tokens)
	{
		if (tokens->type != type && tokens->next && tokens->next->type != type)
			tokens = join_tokens(&tokens, &tokens->next);
		else
		{
			if (tokens->type != type && tokens->next)
				tokens = tokens->next;
			else if (!tokens->next)
				break ;
		}
		if (tokens->type == type)
			break ;
	}
	if (!tokens->next && tokens->type != type)
	{
		error_unclosed_quotes(cmd_tab, index);
		return (NULL);
	}
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
