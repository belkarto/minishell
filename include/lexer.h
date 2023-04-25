/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:07:21 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/25 13:11:41 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdbool.h>
/*
 * enum used to know type of token neather word or special charachter
 * space or pipe....
 */

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
	HEREDOC,
	REDIR_OUT,
}	t_token;

/*
 * this enum used to know the state of the token is it in GENERAL or inside a
 * double or single quote 
 */

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}	t_state;

typedef struct s_elem
{
	char			*content;
	int				len;
	bool			is_ambiguous;
	t_token			type;
	t_state			state;
	struct s_elem	*next;
	struct s_elem	*prev;
	struct s_elem	*head;
	struct s_elem	*tail;
}	t_elem;

t_elem	*generate_tokens(char *command_line);
void	elem_add_tail(t_elem **elem, t_elem *new_elem);
void	print_lexer(t_elem *head);
t_elem	*new_elem(char *con, int len, int token, int state);
t_elem	*lexer(char *line);
int		token(t_elem **list, int *status, char *line);
int		in_quote(t_elem **list, int *status, int picker);
void	elem_clear(t_elem *list);
void	delet_elem(t_elem	**elem);
int		env(t_elem **list, int *status, char *line);
char	**dup_env(char **env);

#endif
