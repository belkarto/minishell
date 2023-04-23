/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_b_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:20:53 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/23 05:03:28 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_elem	*get_file(t_cmd_tab *cmd_tab, t_elem *tokens, t_token redir_type)
{
	t_elem	*tmp;

	if (tokens->type == SPAC || tokens->type == redir_type)
		return (tokens->prev);
	if (tokens->type == ENV && (tokens->state == IN_DQUOTE
			|| tokens->state == GENERAL))
		expand(&tokens, redir_type);
	else if ((tokens->type == QUOTE || tokens->type == DQUOTE)
		&& tokens->state == GENERAL)
	{
		is_expand(tokens, redir_type);
		tokens = delete_quotes(cmd_tab, tokens, tokens->type);
	}
	if (tokens && tokens->next)
	{
		tmp = get_file(cmd_tab, tokens->next, redir_type);
		if (tmp)
			tokens = join_tokens(&tokens, &tmp);
		else
			return (NULL);
	}
	return (tokens);
}

t_elem	*check_file(t_elem *file, t_cmd_tab *cmd_tab)
{
	if (!file || file->type == PIPE || file->type == LESS || file->type == GREAT
		|| file->type == HEREDOC || file->type == REDIR_OUT)
	{
		if (!file && !cmd_tab->syntax_error->display)
		{
			set_syntax_error(cmd_tab);
			ft_putstr_fd("syntax error\n", 2);
		}
		else if (!cmd_tab->syntax_error->display)
		{
			set_syntax_error(cmd_tab);
			ft_putstr_fd("syntax error\n", 2);
		}
		return (NULL);
	}
	return (file);
}
