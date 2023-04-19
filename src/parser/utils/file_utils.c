/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:23:06 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/19 03:24:08 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

t_redir	*file_new(char *file_name, t_token redir_type, bool in_quote)
{
	t_redir	*elem;

	elem = ft_calloc(sizeof(t_redir), 1);
	if (!elem)
		return (NULL);
	elem->file_name = ft_strdup(file_name);
	elem->redir_type = redir_type;
	elem->in_quote = in_quote;
	elem->next = NULL;
	return (elem);
}

void	file_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_elem	*delete_token(t_elem *token)
{
	if (token->next)
	{
		token = token->next;
		delet_elem(&token->prev);
	}
	else
	{
		token = token->prev;
		delet_elem(&token->next);
	}
	return (token);
}

t_elem	*delete_file(t_elem *token)
{
	if (token->next)
	{
		token = token->next;
		delet_elem(&token->prev);
		token = token->prev;
	}
	else
	{
		token = token->prev;
		delet_elem(&token->next);
	}
	return (token);
}

t_elem	*get_file(t_elem *tokens, t_token redir_type)
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
		tokens = delete_quotes(tokens);
	}
	if (tokens->next)
	{
		tmp = get_file(tokens->next, redir_type);
		if (tmp)
			tokens = join_tokens(&tokens, &tmp);
	}
	return (tokens);
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

void	clear_files(t_redir *list)
{
	t_redir *tmp;

	tmp = list;
	while (tmp)
	{
		list = list->next;
		free(tmp->file_name);
		free(tmp);
		tmp = list;
	}
	list = NULL;
}
