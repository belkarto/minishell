/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_file_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:18:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/14 23:25:25 by ohalim           ###   ########.fr       */
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

// int	is_builtin(char *content)
// {
// 	return ((ft_strcmp(content, "echo") == 0)
// 		|| (ft_strcmp(content, "cd") == 0)
// 			|| (ft_strcmp(content, "pwd") == 0)
// 				|| (ft_strcmp(content, "export") == 0)
// 					|| (ft_strcmp(content, "unset") == 0)
// 						|| (ft_strcmp(content, "env") == 0)
// 							|| (ft_strcmp(content, "exit") == 0));
// }

// void	fill_path_and_cmd(t_elem *tokens, t_cmd_tab *cmd_tab)
// {
// 	int	i;

// 	i = 0;
// }
