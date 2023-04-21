/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 04:10:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/21 16:24:31 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <readline/history.h>
#include <stdio.h>

int	general(t_elem **list, int status, char *line)
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

int	herdoc_lexer(t_elem **head, char *line)
{
	int	status;

	status = IN_DQUOTE;
	if (*line == ENV)
		return (env(head, &status, line));
	else
		return (general(head, status, line));
}

char	*join_and_expand_env(t_elem *head)
{
	char	*line;

	line = NULL;
	while (head)
	{
		if (head->type == ENV)
			expand(&head);
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

void	heredoc_content(t_elem **delimiter, int to_expand)
{
	char	*dili;
	char	*content;
	char	*line;

	dili = (*delimiter)->content;
	content = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, dili) == 0)
		{
			free(line);
			break ;
		}
		if (to_expand == 1)
			line = parse_line(line);
		content = ft_strjoin_gnl(content, line);
		content = ft_strjoin_gnl(content, "\n");
		free(line);
	}
	(*delimiter)->content = content;
}
