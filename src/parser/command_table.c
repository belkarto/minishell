/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/18 05:19:57 by ohalim           ###   ########.fr       */
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
	return (cmd);
}

t_cmd_tab	*command_table(char *command_line)
{
	int			len;
	t_elem		*tokens;
	t_elem		*tokens_dup;
	t_cmd_tab	*cmd_tab;

	tokens = generate_tokens(command_line);
	tokens_dup = tokens;
	len = cmd_tab_len(tokens);
	cmd_tab = (t_cmd_tab *)ft_calloc(sizeof(t_cmd_tab), len);
	if (!cmd_tab)
		return (NULL);
	if (len)
		cmd_tab->len = len;
	ft_printf("Len: %d\n", cmd_tab->len);
	iterate_tokens(tokens, cmd_tab);
	// int	i = 0;
	// while (i < cmd_tab->len)
	// {
	// 	while (cmd_tab[i].redir)
	// 	{
	// 		printf("file_name: %s\n", cmd_tab[i].redir->file_name);
	// 		if (cmd_tab[i].redir->redir_type == LESS)
	// 			printf("redir_type: <\n");
	// 		if (cmd_tab[i].redir->redir_type == GREAT)
	// 			printf("redir_type: >\n");
	// 		if (cmd_tab[i].redir->redir_type == HEREDOC)
	// 			printf("redir_type: <<\n");
	// 		if (cmd_tab[i].redir->redir_type == REDIR_OUT)
	// 			printf("redir_type: >>\n");
	// 		if (cmd_tab[i].redir->in_quote == 1)
	// 			printf("bool: 1\n");
	// 		if (cmd_tab[i].redir->in_quote == 0)
	// 			printf("bool: 0\n");
	// 		cmd_tab[i].redir = cmd_tab[i].redir->next;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	fill_cmd_and_env(tokens_dup, cmd_tab);
	// printf_cmd_tab(cmd_tab);
	ft_printf("\nAfter iterate_tokens: \n");
	print_lexer(tokens);
	elem_clear(tokens);
	return (cmd_tab);
}
