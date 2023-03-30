/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/30 20:46:52 by ohalim           ###   ########.fr       */
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
			while (tokens->type == SPAC)
				tokens = tokens->next;
			if (tokens->type == ENV && (tokens->state == GENERAL
			|| tokens->state == IN_DQUOTE) && type != HEREDOC)
				expand(&tokens);
			if (tokens->type == WORD || tokens->type == ENV)
			{
				cmd_tab[i]->redir = ft_calloc(sizeof(t_redir), 1);
				file_add_back(&(cmd_tab[i]->redir), file_new(tokens->content, type));
			}
			else
			{
				ft_printf("apaha: %s\n", tokens->content);
				ft_printf("must throw error\n");
			}
		}
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
}
