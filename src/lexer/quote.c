/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:21:20 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/10 04:54:38 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	single_quote(t_elem **list, int *status)
{
	if (*status == GENERAL)
	{
		elem_add_tail(list, new_elem(ft_strdup("\'"), 1, QUOTE, *status));
		*status = IN_QUOTE;
		return ;
	}
	else if (*status == IN_DQUOTE)
		*status = IN_DQUOTE;
	else
		*status = GENERAL;
	elem_add_tail(list, new_elem(ft_strdup("\'"), 1, QUOTE, *status));
}

static void	double_quote(t_elem **list, int *status)
{
	if (*status == GENERAL)
	{
		elem_add_tail(list, new_elem(ft_strdup("\""), 1, DQUOTE, *status));
		*status = IN_DQUOTE;
		return ;
	}
	else if (*status == IN_QUOTE)
		*status = IN_QUOTE;
	else
		*status = GENERAL;
	elem_add_tail(list, new_elem(ft_strdup("\""), 1, DQUOTE, *status));
}

int	in_quote(t_elem **list, int *status, int picker)
{
	if (picker == 0)
		single_quote(list, status);
	else
		double_quote(list, status);
	return (1);
}
