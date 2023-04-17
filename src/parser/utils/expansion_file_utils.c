/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/17 20:44:40 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int		i;
	int		quote;
	t_token	redir_type;

	i = 0;
	while (tokens)
	{
		if ((tokens->type == QUOTE || tokens->type == DQUOTE)
			&& tokens->state == GENERAL)
			tokens = inside_quotes(tokens);
		else if (tokens->type == ENV && (tokens->state == IN_DQUOTE
			|| tokens->state == GENERAL))
			expand(&tokens);
		else if (tokens->type == LESS || tokens->type == GREAT
			|| tokens->type == HEREDOC || tokens->type == REDIR_OUT)
		{
			redir_type = tokens->type;
			skip_spaces(&tokens);
			if (!check_file(tokens))
				exit(0); // Must free the cmd_tab and the tokens.
			quote = is_in_quote(tokens);
			tokens = get_file(tokens, redir_type);
			if (tokens)
			{
				file_add_back(&cmd_tab[i].redir, file_new(tokens->content, redir_type, quote));
				if (cmd_tab[i].redir->next)
						cmd_tab[i].redir = cmd_tab[i].redir->next;
				ft_printf("file_name: %s\n", cmd_tab[i].redir->file_name);
				if (cmd_tab[i].redir->redir_type == LESS)
					ft_printf("redir_type: <\n");
				if (cmd_tab[i].redir->redir_type == GREAT)
					ft_printf("redir_type: >\n");
				if (cmd_tab[i].redir->redir_type == HEREDOC)
					ft_printf("redir_type: <<\n");
				if (cmd_tab[i].redir->redir_type == REDIR_OUT)
					ft_printf("redir_type: >>\n");
				if (cmd_tab[i].redir->in_quote == 1)
					ft_printf("bool: 1\n");
				if (cmd_tab[i].redir->in_quote == 0)
					ft_printf("bool: 0\n");
			}
			tokens = delete_file(tokens);
		}
		else
			cmd_tab[i].redir = NULL;
		if (tokens->type == PIPE)
			i++;
		if (tokens != NULL)
			tokens = tokens->next;
	}
}

int	is_builtin(char *content)
{
	return ((ft_strcmp(content, "echo") == 0)
		|| (ft_strcmp(content, "cd") == 0)
			|| (ft_strcmp(content, "pwd") == 0)
				|| (ft_strcmp(content, "export") == 0)
					|| (ft_strcmp(content, "unset") == 0)
						|| (ft_strcmp(content, "env") == 0)
							|| (ft_strcmp(content, "exit") == 0));
}

void	delete_spaces(t_elem *tokens)
{
	while (tokens)
	{
		if (tokens->type == SPAC)
			tokens = delete_file(tokens);
		tokens = tokens->next;
	}
}

void	fill_env(t_elem *tokens, t_cmd_tab cmd_tab)
{
	if (is_builtin(tokens->content))
		cmd_tab.env = NULL;
	else
		cmd_tab.env = generate_cmd_env(tokens->content);
}

void	allocate_2d_cmd(t_elem *tokens, t_cmd_tab *cmd_tab)
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
				return ; // MUST FREE
			if (!tokens->next)
				break ;
			i++;
			len = 0;
		}
		else
			len++;
		tokens = tokens->next;
	}
}

void	fill(t_elem **tokens, t_cmd_tab *cmd_tab)
{
	int	i;

	i = 0;
	while ((*tokens))
	{
		if ((*tokens)->type == PIPE)
		{
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
			{
				ft_putstr_fd("syntax error\n", 2);
				exit (0);
			}
			break ;
		}
		if (i == 0)
		{
			if (is_builtin((*tokens)->content))
				cmd_tab->env = NULL;
			else
			{
				cmd_tab->env = generate_cmd_env((*tokens)->content);
				if (!cmd_tab->env)
					cmd_tab->cmd[i++] = NULL;
			}
		}
		cmd_tab->cmd[i++] = ft_strdup((*tokens)->content);
		(*tokens) = (*tokens)->next;
	}
}

void	fill_cmd_and_env(t_elem *tokens, t_cmd_tab *cmd_tab)
{
	int	i;
	t_elem	*tokens_dup;

	i = 0;
	tokens_dup = tokens;
	if (tokens_dup->next)
		tokens_dup = tokens_dup->next;
	delete_spaces(tokens_dup);
	allocate_2d_cmd(tokens_dup, cmd_tab);
	while (i < cmd_tab->len - 1)
		fill(&tokens_dup, &cmd_tab[i++]);
	printf_cmd_tab(cmd_tab);
}
