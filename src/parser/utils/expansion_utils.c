/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:54:21 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/20 09:51:55 by ohalim           ###   ########.fr       */
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
		elem_add_tail(&head, new_elem(env[i], ft_strlen(env[i]), WORD, GENERAL));
		elem_add_tail(&head, new_elem(" ", 1, SPAC, GENERAL));
		i++;
	}
	return (head);
}

void	expand(t_elem **tokens)
{
	t_env	*env;
	// t_elem	*env_val;

	if (ft_strcmp((*tokens)->content, "$?") == 0)
	{		free((*tokens)->content);
		(*tokens)->content = ft_itoa(g_meta.exit_status);
		return ;
	}
	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
		(*tokens)->content = ft_strdup("");
	else
		(*tokens)->content = ft_strdup(env->content);
	// if ((*tokens)->state == GENERAL && (ft_strrchr((*tokens)->content, ' ') + 1))
	// {
	// 	// t_elem *tmp;
	// 	// tmp = NULL;
	// 	// if ((*tokens)->next)
	// 	// 	tmp = (*tokens)->next;
	// 	env_val = split_env(*tokens);
	// 	ft_printf("env_val1: %s\n", env_val->content);
	// 	ft_printf("env_val2: %s\n", env_val->next->content);
	// 	ft_printf("env_val3: %s\n", env_val->next->next->content);
	// 	ft_printf("env_val4: %s\n", env_val->next->next->next->content);
	// 	ft_printf("env_val5: %s\n", env_val->next->next->next->next->content);
	// 	ft_printf("env_val6: %s\n", env_val->next->next->next->next->next->content);
	// 	t_elem *tmp;
	// 	tmp = NULL;
	// 	if ((*tokens)->next)
	// 		tmp = (*tokens)->next;
	// 	(*tokens)->prev->next = env_val;
	// 	if (tmp)
	// 		env_val->tail = tmp;
	// 	// 	(*tokens)->next = tmp;
	// 	// env_val->tail = (*tokens)->next;
	// 	// (*tokens) = (*tokens)->next;
	// 	// delet_elem(&(*tokens)->prev);
	// 	// (*tokens) = env_val->tail;
	// }
	// (*tokens)->type = WORD;
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
