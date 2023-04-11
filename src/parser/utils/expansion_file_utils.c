/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/11 13:00:26 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void	skip_spaces(t_elem **tokens)
{
	while ((*tokens))
	{
		if (ft_strncmp((*tokens)->content, " ", 2) != 0)
			return ;
		(*tokens) = (*tokens)->next;
	}
}

t_elem	*check_file(t_elem *file)
{
	if (!file || file->type == PIPE)
	{
		if (!file)
			ft_putstr_fd("syntax error near unexpected token `newline'", 2);
		else if (file->type == PIPE)
			ft_putstr_fd("syntax error near unexpected token `|'", 2);
		g_meta.exit_status = 258;
		return (NULL);
	}
	return (file);
}

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	(void)cmd_tab;
	t_token	redir_type;

	while (tokens)
	{
		if ((tokens->type == QUOTE || tokens->type == DQUOTE)
			&& tokens->state == GENERAL)
		{
			is_expand(tokens);
			tokens = delete_quotes(tokens);
		}
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE
			|| tokens->state == GENERAL))
			expand(&tokens);
		else if (tokens->type == LESS || tokens->type == GREAT
			|| tokens->type == HEREDOC || tokens->type == REDIR_OUT)
		{
			redir_type = tokens->type;
			skip_spaces(&tokens);
			if (!check_file(tokens))
				exit(0); // Must free the cmd_tab and the tokens.
			// if (redir_type == LESS || redir_type == GREAT || redir_type == REDIR_OUT)
			// 	ft_printf("Not heredoc\n");
			// else if (redir_type)
		}
		if (tokens != NULL)
			tokens = tokens->next;
	}
}
