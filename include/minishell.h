/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:34:54 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/04 01:47:59 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};


typedef struct s_elem
{
	char			    *content;
	int				    len;
	enum e_token	type;
	enum e_state	state;
	struct s_elem			  *next;
	struct s_elem			  *prev;
}	t_elem;

typedef struct s_node
{
	t_elem	*head;
	t_elem	*tail;
	int		  size;
}	t_node;

void	rl_replace_line (const char *, int);
void	signals(void);
void	end_of_file(void);
void	parsing_input(char *input);
#endif
