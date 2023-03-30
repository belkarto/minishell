/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:00:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/19 16:03:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef ENUM_H
# define ENUM_H

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

#endif
