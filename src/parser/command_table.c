/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/18 20:16:25 by belkarto         ###   ########.fr       */
=======
/*   Updated: 2023/04/19 01:05:38 by ohalim           ###   ########.fr       */
>>>>>>> 3a24a11d1f57a04065f165a3ec7425f70295cc6c
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
	if (!tokens)
		return (0);
	while (tokens->next)
	{
		if (tokens->type == PIPE)
			cmd++;
		tokens = tokens->next;
	}
	return (cmd);
}

t_cmd_tab	*command_table(char *command_line)
{
	int			len;
	t_elem		*tokens;
	t_cmd_tab	*cmd_tab;

	tokens = generate_tokens(command_line);
	len = cmd_tab_len(tokens);
	cmd_tab = (t_cmd_tab *)ft_calloc(sizeof(t_cmd_tab), len);
	if (!cmd_tab)
		return (NULL);
	if (len)
		cmd_tab->len = len;
	// ft_printf("Len: %d\n", cmd_tab->len);
	iterate_tokens(tokens, cmd_tab);
<<<<<<< HEAD
	fill_cmd_and_env(tokens_dup, cmd_tab);
	// printf_cmd_tab(cmd_tab);
	// ft_printf("\nAfter iterate_tokens: \n");
	// print_lexer(tokens);

	// print_lexer(tokens);
=======
	fill_cmd_and_env(tokens, cmd_tab);
	printf("\n-----After iterate_tokens-----\n");
	print_lexer(tokens);
	printf_cmd_tab(cmd_tab);
>>>>>>> 3a24a11d1f57a04065f165a3ec7425f70295cc6c
	elem_clear(tokens);
	return (cmd_tab);
}
