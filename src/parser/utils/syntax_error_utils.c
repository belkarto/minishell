/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:50:32 by ohalim            #+#    #+#             */
/*   Updated: 2023/04/23 02:13:38 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_syntax_error(t_cmd_tab *cmd_tab)
{
	cmd_tab->syntax_error = ft_calloc(sizeof(t_error), 1);
	cmd_tab->syntax_error->index = cmd_tab->len - 1;
	cmd_tab->syntax_error->display = 0;
	cmd_tab->syntax_error->error = 0;
}

void	set_syntax_error(t_cmd_tab *cmd_tab)
{
	cmd_tab->syntax_error->display = 1;
	cmd_tab->syntax_error->error = 1;
	cmd_tab->syntax_error->index = cmd_tab->len - 1;
	g_meta.exit_status = 258;
}

t_elem	*error_unclosed_quotes(t_cmd_tab *cmd_tab)
{
	ft_putstr_fd("syntax error\n", 2);
	set_syntax_error(cmd_tab);
	return (NULL);
}
