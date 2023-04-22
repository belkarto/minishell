/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 04:10:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/22 22:04:23 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <signal.h>

static void	sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	exit (1);
}

static int	set_error(t_cmd_tab **cmd_tab, int index, int status)
{
	set_syntax_error(*cmd_tab, index, status);
	return (1);
}

void	get_string(char *dilimiter, int fd_pip[2], int to_expand)
{
	char	*content;
	char	*line;
	size_t	len;

	content = NULL;
	signal(SIGINT, sig_handler);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(dilimiter, line) == 0)
			break ;
		if (to_expand == 1)
			line = parse_line(line);
		content = ft_strjoin_gnl(content, line);
		content = ft_strjoin_gnl(content, "\n");
	}
	len = ft_strlen(content) + 1;
	if (write(fd_pip[1], &len, sizeof(size_t)) == -1)
		exit (1);
	if (write(fd_pip[1], content, len) == -1)
		exit (1);
	close(fd_pip[0]);
	exit(0);
}

int	read_line(int fd_pip[2], t_elem **tokens, t_cmd_tab **cmd_tab, int index)
{
	size_t	len;
	char	*content;

	read(fd_pip[0], &len, sizeof(size_t));
	content = ft_calloc(sizeof(char), len);
	if (!content)
		return (set_error(cmd_tab, index, 1));
	read(fd_pip[0], content, len);
	free((*tokens)->content);
	(*tokens)->content = content;
	return (0);
}

int	heredoc_content(t_elem **delimiter, int to_expand, \
		t_cmd_tab *cmd_tab, int index)
{
	pid_t	pid;
	int		fd_pip[2];
	int		statu;

	if (!(*delimiter))
		return (1);
	if (pipe(fd_pip) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		put_error(NULL, false);
		return (1);
	}
	if (pid == 0)
		get_string((*delimiter)->content, fd_pip, to_expand);
	waitpid(pid, &statu, 0);
	close(fd_pip[1]);
	if (statu == 0)
		read_line(fd_pip, delimiter, &cmd_tab, index);
	else
		return (set_error(&cmd_tab, index, 1));
	return (0);
}
