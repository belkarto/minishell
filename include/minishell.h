/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:34:54 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/30 07:23:41 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "builtings.h"

typedef struct s_data
{
	int		exit_status;
	t_env	*env;
}	t_data;

extern t_data	g_meta;

void	rl_replace_line(const char *str, int state);
void	signals(void);
void	end_of_file(void);
t_env	*init_env(char **env);
void	builtins(t_cmd_tab cmd, char **env);
int		d_strlen(char **list);
#endif
