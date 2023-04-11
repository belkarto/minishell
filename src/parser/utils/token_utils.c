/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:50:32 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/11 13:07:02 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

t_elem	*join_tokens(t_elem **token, t_elem **next_token)
{
	(*token)->content = ft_strjoin_gnl((*token)->content, (*next_token)->content);
	(*token) = (*next_token)->next;
	if ((*token)->prev)
		delet_elem(&(*token)->prev);
	return((*token)->prev);
}

t_elem	*delete_last_quote(t_elem *token)
{
	if (token->next != NULL)
	{
		token = token->next;
		delet_elem(&(token->prev));
	}
	else
	{
		delet_elem(&(token));
		return (NULL);
	}
	return (token->prev);
}

void	error_unclosed_quotes(void)
{
	ft_putstr_fd("syntax error\n", 2);
	g_meta.exit_status = 1;
	exit (0); // Must free the cmd_tab and the tokens.
}

t_elem	*delete_quotes(t_elem *tokens)
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
		error_unclosed_quotes();
	}
	while (tokens)
	{
		if (tokens->type != type && tokens->next && tokens->next->type != type)
			tokens = join_tokens(&tokens, &tokens->next);
		else
		{
			if (tokens->type != type)
				tokens = tokens->next;
		}
		if (tokens->type == type)
			break ;
	}
	if (!tokens)
		error_unclosed_quotes();
	return (delete_last_quote(tokens));
}
