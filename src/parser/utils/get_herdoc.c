/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 04:10:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/20 07:32:10 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"
#include <readline/history.h>
#include <stdio.h>

char	*parse_line(char *line)
{
	t_elem	*tokens;
	t_elem	*tmp;
	char	*parsed_line;
	char	*holder;
	t_env	*env_tmp;

	tokens = generate_tokens(line);
	free(line);
	tmp = tokens;
	parsed_line = NULL;
	while (tmp)
	{
		if (tmp->type == ENV)
		{
			holder = tmp->content;
			env_tmp = get_var(tmp->content + 1,g_meta.env);
			if (env_tmp)
				tmp->content = ft_strdup(env_tmp->content);
			else
				tmp->content = ft_strdup("");
			free(holder);
		}
		parsed_line = ft_strjoin_gnl(parsed_line, ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	elem_clear(tokens);
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
			break ;
		if (to_expand == 1)
			line = parse_line(line);
		content = ft_strjoin_gnl(content, line);
		content = ft_strjoin_gnl(content, "\n");
		free(line);
	}
	(*delimiter)->content = content;
}
