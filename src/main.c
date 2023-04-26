/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:33:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/26 14:33:59 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

t_data	g_meta;

void	get_old_history(void)
{
	char	*line;
	char	*tmp;

	g_meta.fd_history = open("./.minishell_history", O_RDONLY);
	if (g_meta.fd_history == -1)
		return ;
	else
	{
		line = get_next_line(g_meta.fd_history);
		while (line)
		{
			tmp = ft_strtrim(line, "\n");
			add_history(tmp);
			free(tmp);
			free(line);
			line = get_next_line(g_meta.fd_history);
		}
	}
}

void	init_program(int ac, char **av, char **env)
{
	struct termios	term;

	(void)ac;
	(void)av;
	g_meta.exec_env = dup_env(env);
	g_meta.env = init_env(env);
	g_meta.exit_status = 0;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_meta.fd_stdin = dup(STDIN_FILENO);
	g_meta.fd_stdout = dup(STDOUT_FILENO);
	get_old_history();
	printf("\n\t	-USE AT YOUR OWN RISK-	\n\n");
}

static int	ft_str_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_add_history(char *str)
{
	if (!str)
		exit(0);
	if (str && ft_strlen(str) && ft_str_space(str))
	{
		g_meta.fd_history = open("./.minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (g_meta.fd_history != -1)
			ft_putendl_fd(str, g_meta.fd_history);
		add_history(str);
		close(g_meta.fd_history);
		return (0);
	}
	else
	{
		free(str);
		return (1);
	}
}

void	ft_wait_pid(pid_t *pid, int len)
{
	int	i;

	i = -1;
	if (!pid)
		return ;
	while (++i < len)
	{
		if (pid[i] != -1)
		{
			waitpid(pid[i], &g_meta.exit_status, 0);
			g_meta.exit_status = WEXITSTATUS(g_meta.exit_status);
		}
	}
}

char	*ft_readline(void)
{
	char	*line;

	if (g_meta.exit_status == 0)
	{
		line = readline("\033[0;1;3;32m [✓] MINISHELL $> \033[0;37m");
	}
	else
	{
		printf("\033[0;1;3;31m %d ", g_meta.exit_status);
		line = readline("\033[0;1;3;31m [x] MINISHELL $> \033[0;37m");
	}
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	char		*readed;
	pid_t		*pid;
	t_cmd_tab	*cmd_tab;

	init_program(argc, argv, env);
	while (1)
	{
		signals();
		readed = ft_readline();
		if (ft_add_history(readed) == 1)
			continue ;
		signal(SIGINT, SIG_IGN);
		cmd_tab = command_table(readed);
		if (!cmd_tab->syntax_error->error)
		{
			pid = exec_cmd_tab(cmd_tab);
			ft_wait_pid(pid, cmd_tab->len);
			update_env();
			free(pid);
		}
		cmd_tab_free(&cmd_tab, cmd_tab->syntax_error->index);
		free(readed);
	}
	return (0);
}
