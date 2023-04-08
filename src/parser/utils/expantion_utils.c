/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/08 01:46:51 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../../include/minishell.h"

void	expand(t_elem **tokens)
{
	t_env	*env;

	env = get_var((*tokens)->content + 1, g_meta.env);
	free((*tokens)->content);
	if (env == NULL)
		(*tokens)->content = ft_strdup("");
	else
		(*tokens)->content = ft_strdup(env->content);
}

t_elem	*delete_quotes(t_elem *tokens)
{
	t_token	type;

	type = tokens->type;
	tokens = tokens->next;
	delet_elem(&tokens->prev);
	while (tokens)
	{
		if (tokens->type == type)
		{
			tokens = tokens->prev;
			delet_elem(&(tokens->next));
			if (!tokens->next)
				tokens->next = NULL;
			break ;
		}
		tokens = tokens->next;
	}
	return (tokens);
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
		if (tokens->type == ENV && (tokens->state == IN_DQUOTE || tokens->state == GENERAL))
			expand(&tokens);
		tokens = tokens->next;
	}
}

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int		i;

	i = 0;
	(void)cmd_tab;
	while (tokens)
	{
		if ((tokens->type == QUOTE || tokens->type == DQUOTE) && tokens->state == GENERAL)
		{
			is_expand(tokens);
			tokens = delete_quotes(tokens);
			// ft_printf("\nIn iterate_tokens\n");
			// ft_printf("\ndelete_quotes: %s\n", tokens->content);
		}
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE || tokens->state == GENERAL))
			expand(&tokens);
		ft_printf("The content: %s\n", tokens->content);
		tokens = tokens->next;
	}
}






























































/*
	Must not expand on heredoc .
*/
// void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
// {
// 	t_token	type;
// 	int		flag;
// 	(void)cmd_tab;

// 	flag = 1;
// 	while (tokens)
// 	{
// 		if ((tokens->type == DQUOTE || tokens->type == QUOTE) &&
// 			(tokens->state == GENERAL))
// 		{
// 			type = tokens->type;
// 			tokens = tokens->next;
// 			delet_elem(&tokens->prev);
// 			while (tokens && tokens->type != type && tokens->state != GENERAL)
// 			{
// 				if (tokens->type == ENV && tokens->state == IN_DQUOTE)
// 					expand(&tokens);
// 				tokens = tokens->next;
// 			}
// 			if (tokens->next)
// 			{
// 				tokens = tokens->next;
// 				flag = 0;
// 				delet_elem(&tokens->prev);
// 			}
// 			else
// 			{	
// 				delet_elem(&tokens);
// 				break ;
// 			}
// 		}
// 		if (tokens->type == ENV && tokens->state == GENERAL)
// 		{
// 			flag = 1;
// 			expand(&tokens);
// 		}
// 		if (tokens && flag)
// 		{
// 			flag = 1;
// 			tokens = tokens->next;
// 		}
// 	}
// }
// void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
// {
// 	int		i;
// 	int		j;
// 	t_token	type;

// 	i = 0;
// 	j = 0;
// 	while (tokens)
// 	{
// 		if (tokens->type == ENV && (tokens->state == GENERAL
// 			|| tokens->state == IN_DQUOTE))
// 			expand(&tokens);
// 		else if ()
// 			//fuction to join 
// 		else if (tokens->type == LESS || tokens->type == GREAT || tokens->type == HEREDOC
// 			|| tokens->type == REDIR_OUT)
// 		{
// 			//fuction to handle files 
// 			type = tokens->type;
// 			if (tokens->next)
// 			{
// 				tokens = tokens->next;
// 				delet_elem(&tokens->prev);
// 			}
// 			else
// 			{	
// 				delet_elem(&tokens);
// 				break ;
// 			}
// 			while (tokens->next && tokens->type == SPAC)
// 				tokens = tokens->next;
// 			if (tokens->type == ENV && (tokens->state == GENERAL
// 			|| tokens->state == IN_DQUOTE) && type != HEREDOC)
// 				expand(&tokens);
// 			else if (tokens->type == WORD || tokens->type == ENV)
// 			{
// 				cmd_tab[i].redir = ft_calloc(sizeof(t_redir), 1);
// 				file_add_back(&(cmd_tab[i]).redir, file_new(tokens->content, type));
// 				if (tokens->next)
// 				{
// 					tokens = tokens->next;
// 					delet_elem(&tokens->prev);
// 				}
// 				else
// 				{
// 					delet_elem(&tokens);
// 					break ;
// 				}
// 			}
// 			else
// 			{
// 				while (j < i)
// 				{
// 					if (cmd_tab[j].redir)
// 						redir_clear(cmd_tab[j].redir);
// 					j++;
// 				}
// 				ft_putstr_fd("syntax error\n", 2);
// 				break;
// 			}
// 		}
// 		else
// 		{
// 			cmd_tab[i].redir = ft_calloc(sizeof(t_redir), 1);
// 			cmd_tab[i].redir = NULL;
// 		}
// 		if (tokens->type == PIPE)
// 			i++;
// 		if (tokens)
// 			tokens = tokens->next;
// 	}
// }