/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/30 20:50:06 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdlib.h>

t_elem	*generate_tokens(char *command_line)
{
	t_elem	*tokens;

	if (command_line == NULL)
		end_of_file();
	tokens = lexer(command_line);
	return (tokens);
}

int	cmd_tab_len(t_elem *tokens)
{
	int	cmd;

	cmd = 1;
	while (tokens->next)
	{
		if (tokens->type == PIPE)
			cmd++;
		tokens = tokens->next;
	}
	return (cmd + 1);
}

t_cmd_tab	**command_table(char *command_line)
{
	int			i;
	t_elem		*tokens;
	t_cmd_tab	**cmd_tab;

	i = 0;
	tokens = generate_tokens(command_line);
	cmd_tab = (t_cmd_tab **)malloc(cmd_tab_len(tokens) * sizeof(t_cmd_tab *));
	if (!cmd_tab)
		return (NULL);
	while (i < cmd_tab_len(tokens))
	{
		cmd_tab[i] = ft_calloc(sizeof(t_cmd_tab), 1);
		i++;
	}
	iterate_tokens(tokens, cmd_tab);
	print_lexer(tokens);
	elem_clear(tokens);
	return (NULL);
}
