/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:31:27 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/14 00:43:02 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

t_elem	*inside_quotes(t_elem *token)
{
	is_expand(token);
	token = delete_quotes(token);
	return (token);
}

void	skip_spaces(t_elem **tokens)
{
	if (!(*tokens)->next)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2); //Must free the cmd_tab and the tokens.
		g_meta.exit_status = 258;
		exit (0);
	}
	(*tokens) = (*tokens)->next;
	delet_elem(&(*tokens)->prev);
	while ((*tokens))
	{
		if (ft_strncmp((*tokens)->content, " ", 2) != 0)
			return ;
		(*tokens) = (*tokens)->next;
	}
}

int	is_in_quote(t_elem *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->type == LESS || tokens->type == GREAT
			|| tokens->type == HEREDOC || tokens->type == REDIR_OUT)
			break;
		if (tokens->type == QUOTE || tokens->type == DQUOTE)
			i = 0;
		tokens = tokens->next;
	}
	return (i);
}

t_elem	*join_none_space(t_elem *tokens)
{
	while (tokens->next)
	{
		if (tokens->type != WORD || tokens->type == SPAC)
			break ;
		tokens->content = ft_strjoin_gnl(tokens->content, tokens->next->content);
		tokens = tokens->next;
	}
	return (tokens);
}
