/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/10 05:26:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/history.h>

// char	*ft_read_line(int status)
// {
// 	if (status == IN_QUOTE)
// 		return (readline("quote>"));
// 	else
// 		return (readline("dquote>"));
// }

// void	get_rest(t_elem **list, int statu)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	line = ft_read_line(statu);
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("unexpected EOF while looking for matching\n", 2);
// 		exit (258);
// 	}
// 	while (line[i])
// 		i += token(list, &statu, line + i);
// 	if (statu != GENERAL)
// 		get_rest(list, statu);
// }

t_elem	*lexer(char *line)
{
	int		i;
	int		statu;
	t_elem	*head;

	head = NULL;
	statu = GENERAL;
	i = 0;
	while (line[i])
		i += token(&head, &statu, line + i);
	// if (statu != GENERAL)
	// 	get_rest(&head, statu);
	return (head);
}
