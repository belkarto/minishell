/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:02:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/15 10:24:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

typedef struct s_cmd_tab
{
	char	**cmd;
	char	*env;
	int		in_file;
	int		out_file;
}	t_cmd_tab;

void	ft_cd(t_cmd_tab cmd);
void	ft_pwd(t_cmd_tab cmd);
void	ft_exit(t_cmd_tab cmd);
void	ft_export(t_cmd_tab cmd);
#endif
