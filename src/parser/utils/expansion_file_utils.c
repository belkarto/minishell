/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/11 01:55:32 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	(void)cmd_tab;
	while (tokens)
	{
		if ((tokens->type == QUOTE || tokens->type == DQUOTE) && tokens->state == GENERAL)
		{
			is_expand(tokens);
			tokens = delete_quotes(tokens);
		}
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE || tokens->state == GENERAL))
			expand(&tokens);
		if (tokens != NULL)
			tokens = tokens->next;
	}
}
