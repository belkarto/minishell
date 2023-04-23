/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:40:59 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 05:05:12 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	general(t_elem **list, int status, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ENV)
			break ;
		i++;
	}
	elem_add_tail(list, new_elem(ft_substr(line, 0, i), i, WORD, status));
	return (i);
}

static int	herdoc_lexer(t_elem **head, char *line)
{
	int	status;

	status = IN_DQUOTE;
	if (*line == ENV)
		return (env(head, &status, line));
	else
		return (general(head, status, line));
}

static char	*join_and_expand_env(t_elem *head)
{
	char	*line;

	line = NULL;
	while (head)
	{
		if (head->type == ENV)
			expand(&head, head->type);
		line = ft_strjoin_gnl(line, head->content);
		head = head->next;
	}
	return (line);
}

char	*parse_line(char *line)
{
	t_elem	*head;
	int		i;
	char	*parsed_line;

	i = 0;
	head = NULL;
	while (line[i])
		i += herdoc_lexer(&head, line + i);
	parsed_line = join_and_expand_env(head);
	elem_clear(head);
	free(line);
	return (parsed_line);
}
