/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:54:21 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/13 20:55:24 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void	expand(t_elem **tokens)
{
	t_env	*env;
	// t_elem	*tmp;
	// char	**export;

	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
		(*tokens)->content = ft_strdup("");
	else
		(*tokens)->content = ft_strdup(env->content);
	// if (((*tokens)->state) == GENERAL && (ft_strrchr((*tokens)->content, ' ') + 1))
	// {
	// 	export = ft_split((*tokens)->content, ' ');
	// 	(*tokens)->content = *export;
	// 	export++;
	// 	while (*export != NULL)
	// 	{
	// 		tmp = (*tokens)->next;
	// 		(*tokens)->next = new_elem(*export, ft_strlen(*export), WORD, (*tokens)->state);
	// 		(*tokens)->next->next = tmp;
	// 		free (tmp);
	// 		export++;
	// 	}
	// }
	(*tokens)->type = WORD;
}

void	is_expand(t_elem *tokens)
{
	t_token	type;

	type = tokens->type;
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == type)
			return ;
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE || tokens->state == GENERAL))
			expand(&tokens);
		tokens = tokens->next;
	}
}
