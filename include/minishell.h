/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:34:54 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/08 23:29:29 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum e_token
{
	WORD = -1,
	SPAC = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DQUOTE = '\"',
	BACK_SLASH = '\\',
	ENV = '$',
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	HERE_DOC,
	DREDIR_OUT,
}t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}t_state;

typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_elem	*next;
	// struct s_elem	*prev;
	struct s_elem	*head;
	struct s_elem	*tail;
}	t_elem;

typedef struct s_node
{
	t_elem	*head;
	t_elem	*tail;
	int		size;
}	t_node;

void	rl_replace_line(const char *str, int state);
void	signals(void);
void	end_of_file(void);
void	parsing_input(char *input);
void	elem_add_tail(t_elem **elem, t_elem *new_elem);
t_elem	*new_elem(char *con, int len, int token, int state);
t_elem	*lexer(char *line);
#endif
