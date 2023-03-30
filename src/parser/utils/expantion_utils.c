/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/30 07:46:52 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../../include/minishell.h"

static void	expand(t_elem **tokens)
{
	t_env	*env;

	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
		(*tokens)->content = ft_strdup("");
	else
		(*tokens)->content = ft_strdup(env->content);
}

void	iterate_tokens(t_elem *tokens, t_cmd_tab **cmd_tab)
{
	int		i;
	t_token	type;

	i = 0;
	(void)cmd_tab;
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
			delete_elem(&tokens->prev);
			while (tokens->type == SPAC)
			{
				tokens = tokens->next;
				delete_elem(&tokens->prev);
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
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
}
