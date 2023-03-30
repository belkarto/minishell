/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/23 14:18:13 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../../include/minishell.h"

// static void	expand(t_elem **tokens)
// {
// 	t_env	*env;

// 	env = g_meta.env;
// 	while (env)
// 	{
// 		if (ft_strncmp(env->name, ((*tokens)->content + 1), ft_strlen((*tokens)->content + 1)) == 0)
// 			(*tokens)->content = ft_strdup(env->content);
// 		env = env->next;
// 	}
// }

void	iterate_tokens(t_elem *tokens, t_cmd_tab **cmd_tab)
{
	int		i;
	t_token	type;

	i = 0;
	while (tokens)
	{
		if (tokens->type == ENV && (tokens->state == GENERAL
			|| tokens->state == IN_DQUOTE))
			expand(&tokens);
		else if (tokens->type == LESS || tokens->type == GREAT || tokens->type == HEREDOC
			|| tokens->type == REDIR_OUT)
		{
			type = tokens->type;
			tokens = tokens->next;
			delete_elem(tokens->prev);
			while (tokens->type == SPAC)
			{
				tokens = tokens->next;
				delete_elem(tokens->prev);
			}
			if (tokens->type == ENV && (tokens->state == GENERAL
			|| tokens->state == IN_DQUOTE) && type != HEREDOC)
			{
				expand(&tokens);
				
			}
			else if (tokens->type == WORD)
				;
			else
			{
				
			}
		}
		if (tokens.type == PIPE)
			i++;
		tokens = tokens->next;
	}
}