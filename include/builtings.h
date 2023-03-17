/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:02:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/17 08:06:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd_tab
{
	char	**cmd;
	char	*env;
	int		in_file;
	int		out_file;
}	t_cmd_tab;

void	env_add_back(t_env **list, t_env *new_env);
int		join_env(char *name, char *env);
t_env	*new_env(char *env);
char	*get_name(char *env);
void	del_var(t_env *var);
void	ft_cd(t_cmd_tab cmd);
void	ft_pwd(t_cmd_tab cmd);
void	ft_exit(t_cmd_tab cmd);
void	ft_env(t_cmd_tab cmd);
void	ft_export(t_cmd_tab cmd);
void	ft_unset(t_cmd_tab cmd);
#endif
