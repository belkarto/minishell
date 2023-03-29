/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/22 16:19:03 by ohalim           ###   ########.fr       */
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

int	cmd_tab_len(char **commands)
{
	int	len;

	len = 0;
	while (commands[len])
		len++;
	return (len + 1);
}

t_cmd_tab	**command_table(char *command_line)
{
	t_elem		*tokens;
	//t_cmd_tab	**cmd_tab;

	tokens = generate_tokens(command_line);
	iterate_tokens(tokens);
	print_lexer(tokens);
	elem_clear(tokens);
	return (NULL);
}
