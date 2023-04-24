/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:34:54 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/24 11:37:21 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "builtings.h"
# include "execution.h"

typedef struct s_data
{
	int		exit_status;
	t_env	*env;
	int		heredoc;
	char	**exec_env;
	int		fd_stdin;
	int		fd_stdout;
}	t_data;

extern t_data	g_meta;

void	rl_replace_line(const char *str, int state);
void	signals(void);
void	end_of_file(void);
t_env	*init_env(char **env);
void	builtins(t_cmd_tab cmd, bool in_child);
int		d_strlen(char **list);
#endif
