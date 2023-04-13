/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/13 20:18:35 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

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

t_elem	*check_file(t_elem *file)
{
	if (!file || file->type == PIPE || file->type == LESS || file->type == GREAT
		|| file->type == HEREDOC || file->type == REDIR_OUT)
	{
		if (!file)
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		else
		{
			ft_putstr_fd("syntax error near unexpected token ", 2);
			write(2, "`", 1);
			ft_putstr_fd(file->content, 2);
			write(2, "\"\n", 2);
		}
		g_meta.exit_status = 258;
		return (NULL);
	}
	return (file);
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

t_elem	*get_file(t_elem *tokens, t_token redir_type)
{
	t_elem	*tmp;

	if (tokens->type == SPAC)
		return (tokens);
	if (tokens->type == ENV && (tokens->state == IN_DQUOTE
		|| tokens->state == GENERAL))
		expand(&tokens);
	else if ((tokens->type == QUOTE || tokens->type == DQUOTE)
		&& tokens->state == GENERAL)
	{
		is_expand(tokens);
		tokens = delete_quotes(tokens);
	}
	if (tokens->next)
	{
		tmp = get_file(tokens->next, redir_type);
		tokens = join_tokens(&tokens, &tmp);
	}
	return (tokens);
}

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int		i;
	int		in_quote;
	t_token	redir_type;

	i = 0;
	while (tokens)
	{
		// General.
		if ((tokens->type == QUOTE || tokens->type == DQUOTE)
			&& tokens->state == GENERAL)
		{
			is_expand(tokens);
			tokens = delete_quotes(tokens);
		}
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE
			|| tokens->state == GENERAL))
			expand(&tokens);
		// The redirections.
		else if (tokens->type == LESS || tokens->type == GREAT
			|| tokens->type == HEREDOC || tokens->type == REDIR_OUT)
		{
			redir_type = tokens->type;
			skip_spaces(&tokens);
			if (!check_file(tokens))
				exit(0); // Must free the cmd_tab and the tokens.
			// Heredoc.
			if (redir_type != HEREDOC)
			{
				in_quote = is_in_quote(tokens);
				tokens = get_file(tokens, redir_type);
				if (tokens)
				{
					file_add_back(&cmd_tab[i].redir, file_new(tokens->content, redir_type, in_quote));
					if (cmd_tab[i].redir->next)
						cmd_tab[i].redir = cmd_tab[i].redir->next;
					ft_printf("file_name: %s\n", cmd_tab[i].redir->file_name);
					if (cmd_tab[i].redir->redir_type == LESS)
						ft_printf("redir_type: <\n");
					if (cmd_tab[i].redir->redir_type == GREAT)
						ft_printf("redir_type: >\n");
					if (cmd_tab[i].redir->redir_type == HEREDOC)
						ft_printf("redir_type: <<\n");
					if (cmd_tab[i].redir->redir_type == REDIR_OUT)
						ft_printf("redir_type: >>\n");
					if (cmd_tab[i].redir->in_quote == 1)
						ft_printf("bool: 1\n");
					if (cmd_tab[i].redir->in_quote == 0)
						ft_printf("bool: 0\n");
				}
				if (tokens->next)
				{
					tokens = tokens->next;
					delet_elem(&tokens->prev);
					tokens = tokens->prev;
				}
				else
				{
					tokens = tokens->prev;
					delet_elem(&tokens->next);
				}
			}
			// Else.
			else
			{
				in_quote = is_in_quote(tokens);
				tokens = get_file(tokens, redir_type);
				if (tokens)
				{
					file_add_back(&cmd_tab[i].redir, file_new(tokens->content, redir_type, in_quote));
					if (cmd_tab[i].redir->next)
						cmd_tab[i].redir = cmd_tab[i].redir->next;
					ft_printf("file_name: %s\n", cmd_tab[i].redir->file_name);
					if (cmd_tab[i].redir->redir_type == LESS)
						ft_printf("redir_type: <\n");
					if (cmd_tab[i].redir->redir_type == GREAT)
						ft_printf("redir_type: >\n");
					if (cmd_tab[i].redir->redir_type == HEREDOC)
						ft_printf("redir_type: <<\n");
					if (cmd_tab[i].redir->redir_type == REDIR_OUT)
						ft_printf("redir_type: >>\n");
					if (cmd_tab[i].redir->in_quote == 1)
						ft_printf("bool: 1\n");
					if (cmd_tab[i].redir->in_quote == 0)
						ft_printf("bool: 0\n");
				}
				if (tokens->next)
				{
					tokens = tokens->next;
					delet_elem(&tokens->prev);
					tokens = tokens->prev;
				}
				else
				{
					tokens = tokens->prev;
					delet_elem(&tokens->next);
				}
			}
		}
		else
			cmd_tab[i].redir = NULL;
		if (tokens->type == PIPE)
			i++;
		if (tokens != NULL)
			tokens = tokens->next;
		// free (redir_type);
	}
}
