/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:08:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/10 09:20:26 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_type(int type)
{
	if (type == WORD)
		ft_printf("WORD\t\t");
	else if (type == PIPE)
		ft_printf("PIPE\t\t");
	else if (type == LESS)
		ft_printf("LESS\t\t");
	else if (type == HEREDOC)
		ft_printf("HERDOC\t\t");
	else if (type == REDIR_OUT)
		ft_printf("REDIR_OUT\t\t");
	else if (type == GREAT)
		ft_printf("GREAT\t\t");
	else if (type == ENV)
		ft_printf("ENV\t\t");
	else if (type == QUOTE)
		ft_printf("QUOTE\t\t");
	else if (type == DQUOTE)
		ft_printf("DQUOTE\t\t");
	else
		ft_printf("SPAC\t\t");
}

void	ft_print_state(int state)
{
	if (state == GENERAL)
		ft_printf("GENERAL\n");
	else if (state == IN_QUOTE)
		ft_printf("IN_QUOTE\n");
	else
		ft_printf("IN_DQUOTE\n");
}

void	print_lexer(t_elem *head)
{
	ft_printf("|content\t\tlen\t\ttype\t\tstate\n");
	ft_printf("-------------------------------------------------------------\n");
	while (head)
	{
		ft_printf("\'%s\'\t\t\t%d\t\t", head->content, head->len);
		ft_print_type(head->type);
		ft_print_state(head->state);
		head = head->next;
	}
}
