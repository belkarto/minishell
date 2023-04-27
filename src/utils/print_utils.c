/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:08:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/26 19:04:32 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

void	ft_print_type(int type)
{
	if (type == WORD)
		printf("WORD\t\t");
	else if (type == PIPE)
		printf("PIPE\t\t");
	else if (type == LESS)
		printf("LESS\t\t");
	else if (type == HEREDOC)
		printf("HERDOC\t\t");
	else if (type == REDIR_OUT)
		printf("APPAND\t\t");
	else if (type == GREAT)
		printf("GREAT\t\t");
	else if (type == ENV)
		printf("ENV\t\t");
	else if (type == QUOTE)
		printf("QUOTE\t\t");
	else if (type == DQUOTE)
		printf("DQUOTE\t\t");
	else
		printf("SPAC\t\t");
}

void	ft_print_state(int state)
{
	if (state == GENERAL)
		printf("GENERAL\n");
	else if (state == IN_QUOTE)
		printf("IN_QUOTE\n");
	else
		printf("IN_DQUOTE\n");
}

void	print_lexer(t_elem *head)
{
	t_elem	*tmp;

	tmp = head;
	printf("|content\t\tlen\t\ttype\t\tstate\n");
	printf("-------------------------------------------------------------\n");
	while (tmp)
	{
		printf("%s\t\t\t%d\t\t", tmp->content, tmp->len);
		ft_print_type(tmp->type);
		ft_print_state(tmp->state);
		tmp = tmp->next;
	}
}

void	printf_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_tab->len)
	{
		j = -1;
		printf("cmd_and_args:\t");
		while (cmd_tab[i].cmd[++j])
		{
			printf("%s\t", cmd_tab[i].cmd[j]);
		}
		printf("redirictions  ");
		while (cmd_tab[i].redir)
		{
			printf("file_name : %s", cmd_tab[i].redir->file_name);
			if (cmd_tab[i].redir->redir_type == HEREDOC)
				printf("rediriction_type : <<\n");
			else if (cmd_tab[i].redir->redir_type == REDIR_OUT)
				printf("rediriction_type : >>\n");
			else
				printf("rediriction_type : %c\n", cmd_tab[i].redir->redir_type);
			cmd_tab[i].redir = cmd_tab[i].redir->next;
		}
		printf("\n--------------------------------------------------------------------------------------\n");
	}
}
