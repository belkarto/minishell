/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:54:21 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/20 10:52:16 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

t_elem	*split_env(t_elem *tokens)
{
	int		i;
	char	**env;
	t_elem	*head;

	i = 0;
	head = NULL;
	env = ft_split(tokens->content, ' ');
	while (env[i] != NULL)
	{
		elem_add_tail(&head, new_elem(ft_strdup(env[i]), ft_strlen(env[i]), WORD, GENERAL));
		elem_add_tail(&head, new_elem(ft_strdup(" "), 1, SPAC, GENERAL));
		i++;
	}
	return (head);
}

void	expand(t_elem **tokens)
{
	t_env	*env;
	t_elem	*env_val;

	if (ft_strcmp((*tokens)->content, "$?") == 0)
	{		free((*tokens)->content);
		(*tokens)->content = ft_itoa(g_meta.exit_status);
		return ;
	}
	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
	{
		(*tokens)->content = ft_strdup("");
		return ;
	}
	else
		(*tokens)->content = ft_strdup(env->content);
	if ((*tokens)->state == GENERAL && (ft_strrchr((*tokens)->content, ' ') + 1))
	{
		env_val = split_env(*tokens);
		env_val->tail->next = (*tokens)->next;
		(*tokens)->next = env_val;
		env_val->prev = (*tokens);
		delet_elem(&env_val->prev);
		(*tokens) = env_val;
		(void)env_val;
	}
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
