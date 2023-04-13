/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/12 06:15:05 by ohalim           ###   ########.fr       */
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
	ft_printf("Before iterate_tokens:\n");
	print_lexer(tokens);
	return (tokens);
}

int	cmd_tab_len(t_elem *tokens)
{
	int	cmd;

	cmd = 1;
	if (!tokens)
		return (0);
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
	int			len;
	int			i;
	t_elem		*tokens;
	t_cmd_tab	*cmd_tab;

	i = 0;
	tokens = generate_tokens(command_line);
	len = cmd_tab_len(tokens);
	cmd_tab = (t_cmd_tab *)malloc(len * sizeof(t_cmd_tab));
	if (!cmd_tab)
		return (NULL);
	if (len)
		cmd_tab->len = len;
	iterate_tokens(tokens, cmd_tab);
	print_lexer(tokens);
	elem_clear(tokens);
	return (NULL);
}
