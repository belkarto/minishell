/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:58:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/03/19 16:09:30 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_redir
{
	char			*file_name;
	enum e_token	redir_type;
}	t_redir;

typedef struct s_cmd_tab
{
	char	**cmd;
	char	*env;
	t_redir	*redir;
	bool	pip;
}	t_cmd_tab;

//------------------Char_Utils----------------------//
char	*free_2d(char **tab);


//------------------Path_utils----------------------//
char	*generate_cmd_env(char *cmd);

//--------------------Cmd_Tab-----------------------//
t_cmd_tab	**command_table(char *command_line);

#endif
