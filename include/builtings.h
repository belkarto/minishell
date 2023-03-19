/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:02:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/18 08:06:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

# include "parser.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;


void	env_add_back(t_env **list, t_env *new_env);
int		join_env(char *name, char *env);
t_env	*new_env(char *env);
char	*get_name(char *env);
t_env	*builtin_env(void);
void	update_env(void);
void	shell_lvl(t_env *list);
t_env	*get_var(char *name, t_env *list);
void	del_var(t_env *var);
void	ft_cd(t_cmd_tab cmd);
void	ft_pwd(t_cmd_tab cmd);
void	ft_exit(t_cmd_tab cmd);
void	ft_env(t_cmd_tab cmd);
void	ft_export(t_cmd_tab cmd);
void	ft_unset(t_cmd_tab cmd);
#endif
