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

static void	expand(t_elem **tokens)
{
	t_env	*env;

	env = g_meta.env;
	while (env)
	{
		if (ft_strncmp(env->name, ((*tokens)->content + 1), ft_strlen((*tokens)->content + 1)) == 0)
			(*tokens)->content = ft_strdup(env->content);
		env = env->next;
	}
}

void	iterate_tokens(t_elem *tokens)
{
	while (tokens)
	{
		if (tokens->type == ENV && (tokens->state == GENERAL || tokens->state == IN_DQUOTE))
			expand(&tokens);
		tokens = tokens->next;
	}
}
