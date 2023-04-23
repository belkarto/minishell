/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/23 00:19:20 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	allocate_2d_cmd(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (1)
	{
		if (tokens->type == PIPE || !tokens->next)
		{
			if (!tokens->next)
				len += 1;
			cmd_tab[i].cmd = (char **)ft_calloc(sizeof(char *), (len + 1));
			if (!cmd_tab[i].cmd)
				return ;
			if (!tokens->next)
				break ;
			i++;
			len = 0;
		}
		else
			len++;
		if (tokens->next)
			tokens = tokens->next;
	}
}

static int	fill(t_elem **tokens, t_cmd_tab *cmd_tab)
{
	int	i;

	i = 0;
	cmd_tab->env = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == PIPE)
		{
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
				return (1);
			break ;
		}
		if ((*tokens)->content[0] != 0)
			cmd_tab->cmd[i++] = ft_strdup((*tokens)->content);
		(*tokens) = (*tokens)->next;
	}
	return (0);
}

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int		i;
	int		quote;
	t_token	redir_type;

	i = 0;
	g_meta.heredoc = 0;
	while (tokens)
	{
		if ((tokens->type == QUOTE || tokens->type == DQUOTE)
			&& tokens->state == GENERAL)
			tokens = inside_quotes(cmd_tab, tokens, i);
		else if (tokens && tokens->type == ENV && (tokens->state == IN_DQUOTE
				|| tokens->state == GENERAL))
			expand(&tokens);
		else if (tokens && (tokens->type == LESS || tokens->type == GREAT
				|| tokens->type == HEREDOC || tokens->type == REDIR_OUT))
		{
			redir_type = tokens->type;
			skip_spaces(&tokens);
			if (!check_file(tokens, cmd_tab, i))
				return ;
			quote = is_in_quote(tokens);
			tokens = get_file(cmd_tab, tokens, redir_type, i);
			if (tokens)
				file_add_back(&cmd_tab[i].redir,
					file_new(tokens->content, redir_type, quote));
			tokens = delete_file(tokens);
		}
		if (tokens && tokens->type == PIPE)
			i++;
		if (tokens != NULL)
			tokens = tokens->next;
	}
}

void	fill_cmd_and_env(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int		i;
	t_elem	*tokens_dup;
	t_elem	*holder;

	i = 0;
	tokens_dup = tokens;
	holder = tokens;
	delete_space(&tokens_dup);
	if (holder->content == NULL)
	{
		if (holder->next)
			holder = holder->next;
	}
	allocate_2d_cmd(holder, cmd_tab);
	while (i < cmd_tab->len)
	{
		if (fill(&holder, &cmd_tab[i]) == 1
			&& !cmd_tab->syntax_error->display)
		{
			set_syntax_error(cmd_tab, i, 258);
			ft_putstr_fd("pipe syntax error\n", 2);
			return ;
		}
		i++;
	}
}
