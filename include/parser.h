/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:58:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/20 09:50:31 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_redir
{
	char			*file_name;
	t_token			redir_type;
	bool			in_quote;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_tab
{
	char	**cmd;
	char	*env;
	t_redir	*redir;
	int		len;
}	t_cmd_tab;

//------------------Char_Utils----------------------//
char	*free_2d(char **tab);
int		double_len(char **tab);

//------------------Path_utils----------------------//
char	*generate_cmd_env(char *cmd);

//------------------Expansion_file_utils-----------------//
void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab);
void	fill_cmd_and_env(t_elem *tokens, t_cmd_tab *cmd_tab);

//--------------------Cmd_Tab-----------------------//
t_cmd_tab	*command_table(char *command_line);

//--------------------File_utils_a--------------------//
t_redir	*file_new(char *file_name, t_token redir_type, bool in_quote);
void	file_add_back(t_redir **lst, t_redir *new);
t_elem	*delete_file(t_elem *token);
t_elem	*get_file(t_elem *tokens, t_token redir_type);
t_elem	*check_file(t_elem *file);

//-------------------Expansion_utils-----------------//
void	expand(t_elem **tokens);
void	is_expand(t_elem *tokens);

//--------------------Token_utils--------------------//
t_elem	*join_tokens(t_elem **token, t_elem **next_token);
t_elem	*delete_quotes(t_elem *tokens);
t_elem	*delete_last_quote(t_elem *token);
void	join_unseparated_tokens(t_elem *tokens);

//-----------------Iterate_tokens_utils--------------//
t_elem	*inside_quotes(t_elem *token);
void	skip_spaces(t_elem **tokens);
int		is_in_quote(t_elem *tokens);
t_elem	*join_none_space(t_elem *tokens);
int		is_builtin(char *content);

void	printf_cmd_tab( t_cmd_tab *cmd_tab);

#endif
