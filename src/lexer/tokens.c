  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 05:00:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/10 09:18:49 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word(t_elem **list, int status, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SPAC || line[i] == PIPE || line[i] == ENV
			|| line[i] == LESS || line[i] == GREAT || line[i] == QUOTE
			|| line[i] == DQUOTE)
			break ;
		i++;
	}
	elem_add_tail(list, new_elem(ft_substr(line, 0, i), i, WORD, status));
	return (i);
}

int	tokens(t_elem **list, int *status, int token)
{
	if (token == PIPE)
		elem_add_tail(list, new_elem(ft_strdup("|"), 1, PIPE, *status));
	else if (token == LESS)
		elem_add_tail(list, new_elem(ft_strdup("<"), 1, LESS, *status));
	else if (token == GREAT)
		elem_add_tail(list, new_elem(ft_strdup(">"), 1, GREAT, *status));
	else if (token == SPAC)
		elem_add_tail(list, new_elem(ft_strdup(" "), 1, SPAC, *status));
	else if (token == HEREDOC)
	{
		elem_add_tail(list, new_elem(ft_strdup("<<"), 2, HEREDOC, *status));
		return (2);
	}
	else if (token == REDIR_OUT)
	{
		elem_add_tail(list, new_elem(ft_strdup(">>"), 2, REDIR_OUT, *status));
		return (2);
	}
	return (1);
}

int	env(t_elem **list, int *status, char *line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if (ft_isalnum(line[i]) || line[i] == '_')
			continue ;
		else
			break ;
	}
	elem_add_tail(list, new_elem(ft_substr(line, 0, i), i, ENV, *status));
	return (i);
}

int	token(t_elem **list, int *status, char *line)
{
	if (ft_isalnum(*line) || *line == '_')
		return (word(list, *status, line));
	else if (*line == PIPE)
		return (tokens(list, status, PIPE));
	else if (*line == LESS && line[1] == LESS)
		return (tokens(list, status, HEREDOC));
	else if (*line == LESS)
		return (tokens(list, status, LESS));
	else if (*line == GREAT && line[1] == GREAT)
		return (tokens(list, status, REDIR_OUT));
	else if (*line == GREAT)
		return (tokens(list, status, GREAT));
	else if (*line == SPAC)
		return (tokens(list, status, SPAC));
	else if (*line == ENV)
		return (env(list, status, line));
	else if (*line == QUOTE)
		return (in_quote(list, status, 0));
	else if (*line == DQUOTE)
		return (in_quote(list, status, 1));
	return (1);
}
