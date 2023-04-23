/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:08:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/23 06:27:38 by belkarto         ###   ########.fr       */
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
		printf("REDIR_OUT\t\t");
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


void	print_cmd(t_cmd_tab cmd)
{
	int		i;
	t_redir	*tmp;

	i = -1;
	while (cmd.cmd[++i])
	{
		printf("%s  |  ", cmd.cmd[i]);
	}
	printf("\npath --> %s\n", cmd.env);
	tmp = cmd.redir;
	while (tmp)
	{
		printf("%s %c", tmp->file_name, tmp->redir_type);
		tmp = tmp->next;
	}
	printf("\n");
}


void	print_cmd_tab(t_cmd_tab *tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (++i < tab->len)
	{
		print_cmd(tab[i]);
	}
}

void	printf_cmd_tab(t_cmd_tab *cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_tab->len)
	{
		printf("env: %s\ncmd: ", cmd_tab[i].env);
		while (cmd_tab[i].cmd[j])
		{
			printf("%s|", cmd_tab[i].cmd[j]);
			j++;
		}
		if (!cmd_tab[i].cmd[j])
			printf("%s\n\n", cmd_tab[i].cmd[j]);
		printf("\n");
		j = 0;
		i++;
	}
}
