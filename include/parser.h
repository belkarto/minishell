/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:58:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/22 15:44:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_error
{
	int		index;
	bool	error;
	bool	display;
}	t_error;

typedef struct s_redir
{
	char			*file_name;
	t_token			redir_type;
	bool			in_quote;
	char			*herdoc_content;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_tab
{
	t_error	*syntax_error;
	char	**cmd;
	char	*env;
	t_redir	*redir;
	int		len;
}	t_cmd_tab;

//------------------Char_Utils----------------------//
char		*free_2d(char **tab);
int			double_len(char **tab);

//------------------Path_utils----------------------// check
char		*generate_cmd_env(char *cmd);
int			is_builtin(char *content);

//------------------Expansion_file_utils-----------------//
void		iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab);
void		fill_cmd_and_env(t_elem *tokens, t_cmd_tab *cmd_tab);

//--------------------Cmd_Tab-----------------------//  check
t_cmd_tab	*command_table(char *command_line);

//--------------------File_utils_a--------------------//
t_redir		*file_new(char *file_name, t_token redir_type, bool in_quote);
void		file_add_back(t_redir **lst, t_redir *new);
t_elem		*delete_file(t_elem *token);
void		clear_files(t_redir *list);

//--------------------File_utils_b--------------------//
t_elem		*get_file(t_cmd_tab *cmd_tab, t_elem *tokens,
				t_token redir_type, int index);
t_elem		*check_file(t_elem *file, t_cmd_tab *cmd_tab, int index);

//-------------------Expansion_utils-----------------//
void		expand(t_elem **tokens);
void		is_expand(t_elem *tokens);

//--------------------Token_utils--------------------//
t_elem		*join_tokens(t_elem **token, t_elem **next_token);
void		join_unseparated_tokens(t_elem *tokens);
void		delete_space(t_elem **tokens);
t_elem		*delete_token(t_elem *token);

//--------------------Syntax_error_utils--------------------//
void		error_unclosed_quotes(t_cmd_tab *cmd_tab, int index);
void		set_syntax_error(t_cmd_tab *cmd_tab, int index, int statu);
void		init_syntax_error(t_cmd_tab *cmd_tab);

//--------------------Quotes_utils--------------------//
t_elem		*delete_quotes(t_cmd_tab *cmd_tab, t_elem *tokens, int index);
t_elem		*delete_last_quote(t_elem *token);
int			is_in_quote(t_elem *tokens);

//-----------------Iterate_tokens_utils--------------//
t_elem		*inside_quotes(t_cmd_tab *cmd_tab, t_elem *token, int index);
void		skip_spaces(t_elem **tokens);
t_elem		*join_none_space(t_elem *tokens);

void		printf_cmd_tab( t_cmd_tab *cmd_tab);
int			heredoc_content(t_elem **delimiter, int to_expand, t_cmd_tab *cmt_tab, int index);

#endif
