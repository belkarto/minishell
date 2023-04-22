/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_b_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:20:53 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/22 16:05:24 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*get_file(t_cmd_tab *cmd_tab, t_elem *tokens,
		t_token redir_type, int index)
{
	t_elem	*tmp;

	if (tokens->type == SPAC || tokens->type == redir_type)
		return (tokens->prev);
	if (tokens->type == ENV && (tokens->state == IN_DQUOTE
			|| tokens->state == GENERAL))
	{
		if (redir_type != HEREDOC)
			expand(&tokens);
	}
	else if ((tokens->type == QUOTE || tokens->type == DQUOTE)
		&& tokens->state == GENERAL)
	{
		if (redir_type != HEREDOC)
			is_expand(tokens);
		tokens = delete_quotes(cmd_tab, tokens, index);
	}
	if (tokens->next)
	{
		tmp = get_file(cmd_tab, tokens->next, redir_type, index);
		if (tmp)
			tokens = join_tokens(&tokens, &tmp);
	}
	return (tokens);
}

t_elem	*check_file(t_elem *file, t_cmd_tab *cmd_tab, int index)
{
	if (!file || file->type == PIPE || file->type == LESS || file->type == GREAT
		|| file->type == HEREDOC || file->type == REDIR_OUT)
	{
		if (!file && !cmd_tab->syntax_error->display)
		{
			set_syntax_error(cmd_tab, index, 258);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		}
		else if (!cmd_tab->syntax_error->display)
		{
			set_syntax_error(cmd_tab, index, 258);
			ft_putstr_fd("syntax error near unexpected token ", 2);
			write(2, "`", 1);
			ft_putstr_fd(file->content, 2);
			write(2, "\"\n", 2);
		}
		return (NULL);
	}
	return (file);
}
