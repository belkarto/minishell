/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:38:14 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/21 18:12:49 by belkarto         ###   ########.fr       */
/*   Updated: 2023/04/21 10:34:11 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <errno.h>
# include <sys/types.h>
# include "parser.h"

typedef enum e_phase
{
	ONLY_CMD,
	FIRST,
	MIDDLE,
	LAST,
}t_phase;

typedef struct s_pipe
{
	int	*read_end;
	int	*write_end;
}	t_pipe;

typedef struct s_heredoc
{
	int	fd_pipe[2];
	int	len;
}	t_heredoc;

pid_t		*exec_cmd_tab(t_cmd_tab *cmd_tab, char **env);
int		open_out_file(t_redir files);
int		open_in_file(t_redir files);
void		put_error(char *error, bool state);
pid_t		exec_cmd(t_cmd_tab cmd, t_pipe fd_pipe, int len, int ind, char **env);
pid_t		exec_one(t_cmd_tab cmd, char **env);
void		cmd_tab_free(t_cmd_tab **cmd_tab, int len);
void		clear_files(t_redir *list);
void		print_cmd_tab(t_cmd_tab *tab);
t_heredoc	*open_heredoc(t_cmd_tab *tab);

#endif
