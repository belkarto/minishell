/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/02 06:51:50 by ohalim           ###   ########.fr       */
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
	t_redir	*tmp;
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
			delet_elem(&tokens->prev);
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
				i = 0;
				while (cmd_tab[i])
				{
					while (cmd_tab[i]->redir)
					{
						tmp = cmd_tab[i]->redir;
						free(cmd_tab[i]->redir);
						cmd_tab[i]->redir = tmp;
					}
					i++;
				}
				ft_putstr_fd("syntax error", 2);
			}
		}
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
}
