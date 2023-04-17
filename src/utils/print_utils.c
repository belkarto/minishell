/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:08:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/17 01:56:41 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
