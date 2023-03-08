/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/07 02:23:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_elem	*new_elem(char *con, int len, int token, int state)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	elem->state = state;
	elem->type	= token;
	elem->len = len;
	elem->content = con;
	return (elem);
}

int	word(t_list **list, int status, char *line)
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
	ft_lstadd_back(list, ft_lstnew(new_elem(ft_substr(line, 0, i), i, WORD, status)));
	return (i);
}

int	in_quote(t_list **list, int *status, int picker)
{
	if (picker == 0)
	{
		if (*status == GENERAL)
			*status = IN_QUOTE;
		else
			*status = GENERAL;
		(void)list;
		ft_lstadd_back(list, ft_lstnew(new_elem(ft_strdup("\'") , 1, QUOTE, *status)));
	}
	else
	{
		if (*status == GENERAL)
			*status = IN_DQUOTE;
		else
			*status = GENERAL;
		ft_lstadd_back(list, ft_lstnew(new_elem(ft_strdup("\"") , 1, DQUOTE, *status)));
	}
	return (1);
}

int	tokens(t_list **list, int *status, int token)
{
	if (token == PIPE)
		ft_lstadd_back(list, ft_lstnew(new_elem(ft_strdup("|") , 1, PIPE, *status)));
	else if (token == LESS)
		ft_lstadd_back(list, ft_lstnew(new_elem(ft_strdup("<") , 1, LESS, *status)));
	else if (token == GREAT)
		ft_lstadd_back(list, ft_lstnew(new_elem(ft_strdup(">") , 1, GREAT, *status)));
	return (1);

}

int	env(t_list **list, int *status, char *line)
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
	ft_lstadd_back(list, ft_lstnew(new_elem(ft_substr(line, 0, i), i, ENV, *status)));
	return (i);
}

int	token(t_list **list, int *status, char *line)
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

void	printf_list(t_list *head)
{
	t_elem *test;
	ft_printf("|content\t\tlen\t\ttype\t\tstate\n");
	ft_printf("---------------------------------------------------------\n");
	while (head)
	{
		test = head->content;
		ft_printf("|%s\t\t%d\t\t%d\t\t%d\n", test->content, test->len, test->type, test->state);
		head = head->next;
	}
}

t_elem	*lexer(char *line)
{
	t_list	*head;
	int		i;
	int		statu;

	statu = GENERAL;
	i = 0;
	while (line[i])
	{
		i += token(&head, &statu, line + i);
	}
	// printf_list(head);
	return (NULL);
}
