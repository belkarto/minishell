/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:58:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/04 21:19:32 by ohalim           ###   ########.fr       */
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
	bool	pip;
	int		len;
}	t_cmd_tab;

//------------------Char_Utils----------------------//
char	*free_2d(char **tab);


//------------------Path_utils----------------------//
char	*generate_cmd_env(char *cmd);

//------------------Expantion_utils-----------------//
void	iterate_tokens(t_elem *tokens, t_cmd_tab *cmd_tab);

//--------------------Cmd_Tab-----------------------//
t_cmd_tab	**command_table(char *command_line);

//--------------------File_utils--------------------//
t_redir	*file_new(char *file_name, t_token redir_type);
void	file_add_back(t_redir **lst, t_redir *new);
void	redir_clear(t_redir *list);

#endif
