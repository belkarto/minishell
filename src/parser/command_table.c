/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/13 05:21:02 by belkarto         ###   ########.fr       */
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
	print_lexer(tokens);
	return (tokens);
}

int	cmd_len(t_elem *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		if (ft_strncmp(tokens->content, "|", 1) == 0)
			len++;
		tokens = tokens->next;
	}
	return (len + 2);
}

t_cmd_tab	**command_table(char *command_line)
{
	t_elem		*tokens;
	t_cmd_tab	**cmd_tab;
	char		*env;

	tokens = generate_tokens(command_line);
	//cmd_tab = ft_calloc(cmd_len(tokens), sizeof(t_cmd_tab *));
	// if (!cmd_tab)
	// 	return (NULL);
	while (tokens)
	{
		while (tokens && ft_strncmp(tokens->content, "|", 1) != 0)
		{
			env = generate_cmd_env(tokens->content);
			if (!env)
			{
				ft_putstr_fd("command not found\n", 2);
				g_meta.ex_statu = 127;
			}
			else
				printf("env = %s\n", env);
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	(void)cmd_tab;
	free(env);
	elem_clear(tokens);
	return (NULL);
}
