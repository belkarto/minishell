/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/08 23:34:50 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word(t_elem *list, int status, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SPACE || line[i] == PIPE || line[i] == ENV 
			|| line[i] == LESS || line[i] == GREAT || line[i] == QUOTE
			|| line[i] == DQUOTE)
			break ;
		i++;
	}
	elem_add_tail(&list, new_elem(ft_substr(line, 0, i), i, WORD, status));
	return (i);
}

int	in_quote(t_elem *list, int *status, int picker)
{
	if (picker == 0)
	{
		if (*status == GENERAL)
			*status = IN_QUOTE;
		else
			*status = GENERAL;
		(void)list;
		elem_add_tail(&list, new_elem(ft_strdup("\'"), 1, QUOTE, *status));
	}
	else
	{
		if (*status == GENERAL)
			*status = IN_DQUOTE;
		else
			*status = GENERAL;
		elem_add_tail(&list, new_elem(ft_strdup("\"") , 1, DQUOTE, *status));
	}
	return (1);
}

int	tokens(t_elem *list, int *status, int token)
{
	if (token == PIPE)
		elem_add_tail(&list, new_elem(ft_strdup("|") , 1, PIPE, *status));
	else if (token == LESS)
		elem_add_tail(&list, new_elem(ft_strdup("<") , 1, LESS, *status));
	else if (token == GREAT)
		elem_add_tail(&list, new_elem(ft_strdup(">") , 1, GREAT, *status));
	return (1);

}

int	env(t_elem *list, int *status, char *line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if (ft_isalnum(line[i]) || line[i] == '_')
			continue;
		else
			break;
	}
	elem_add_tail(&list, new_elem(ft_substr(line, 0, i), i, ENV, *status));
	return (i);
}

int	token(t_elem *list, int *status, char *line)
{
	if (ft_isalnum(*line) || *line == '_')
		return (word(list, *status, line));
	else if (*line == PIPE)
		return(tokens(list, status, PIPE));
	else if (*line == LESS)
		return(tokens(list, status, LESS));
	else if (*line == GREAT)
		return(tokens(list, status, GREAT));
	else if (*line == ENV)
		return(env(list, status, line));
	else if (*line == QUOTE)
		return (in_quote(list, status, 0));
	else if (*line == DQUOTE)
		return (in_quote(list, status, 1));
	return (1);
}

void	printf_list(t_elem *head)
{
	ft_printf("|content\t\tlen\t\ttype\t\tstate\n");
	ft_printf("---------------------------------------------------------\n");
	while (head)
	{
		ft_printf("|%s\t\t%d\t\t%d\t\t%d\n", head->content, head->len, head->type, head->state);
		head = head->next;
	}
}

t_elem	*lexer(char *line)
{
	int		i;
	int		statu;
	t_elem	*head;

	head = NULL;
	statu = GENERAL;
	i = 0;
	while (line[i])
	{
		i += token(head, &statu, line + i);
	}
	printf_list(head);
	return (NULL);
}
