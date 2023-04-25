/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:54:21 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/25 12:44:26 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_elem	*split_env(t_elem *tokens)
{
	int		i;
	bool	is_ambiguous;
	char	**env;
	t_elem	*head;

	i = 0;
	is_ambiguous = 1;
	head = NULL;
	env = ft_split(tokens->content, ' ');
	if (double_len(env) == 1)
		is_ambiguous = 0;
	while (env[i] != NULL)
	{
		elem_add_tail(&head, new_elem(ft_strdup(env[i]), ft_strlen(env[i]),
				WORD, GENERAL));
		elem_add_tail(&head, new_elem(ft_strdup(" "), 1, SPAC, GENERAL));
		i++;
	}
	if (head && !is_ambiguous)
		head->is_ambiguous = 0;
	else if (head && is_ambiguous)
		head->is_ambiguous = 1;
	free_2d(env);
	return (head);
}

static int	re_tokenize(t_elem **tokens)
{
	t_elem	*env_val;

	env_val = split_env(*tokens);
	if (!env_val)
		return (1);
	env_val->tail->next = (*tokens)->next;
	(*tokens)->next = env_val;
	env_val->prev = (*tokens);
	delet_elem(&env_val->prev);
	(*tokens) = env_val;
	if (env_val->is_ambiguous)
		return (1);
	return (0);
}

int	expand(t_elem **tokens, t_token redir_type)
{
	t_env	*env;

	if (redir_type == HEREDOC)
		return (0);
	if (ft_strcmp((*tokens)->content, "$?") == 0)
	{
		free((*tokens)->content);
		(*tokens)->content = ft_itoa(g_meta.exit_status);
		(*tokens)->type = WORD;
		return (0);
	}
	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
	{
		(*tokens)->content = ft_strdup("");
		return (1);
	}
	(*tokens)->content = ft_strdup(env->content);
	if ((*tokens)->state == GENERAL && ft_strrchr((*tokens)->content, ' '))
		return(re_tokenize(tokens));
	(*tokens)->type = WORD;
	return (0);
}

void	is_expand(t_elem *tokens, t_token redir_type)
{
	if (redir_type == HEREDOC)
		return ;
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == redir_type)
			return ;
		else if (tokens->type == ENV
			&& (tokens->state == IN_DQUOTE || tokens->state == GENERAL))
			tokens->is_ambiguous = expand(&tokens, redir_type);
		tokens = tokens->next;
	}
}
