/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:35:54 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 22:35:56 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_env(char *new_path, char *old_path, t_env **env)
{
	new_path = ft_strjoin_f("PWD=", new_path, 2);
	old_path = ft_strjoin_f("OLDPWD=", old_path, 2);
	ft_export_declare(env, new_path, true, true);
	ft_export_declare(env, old_path, true, true);
	ft_strdel(&old_path);
	ft_strdel(&new_path);
}

int		swap_paths(t_env **env)
{
	t_env	*p_env;
	char	*pwd;
	char	*old_pwd;
	char	*final_old_pwd;

	p_env = *env;
	pwd = get_var("PWD", &p_env);
	old_pwd = get_var("OLDPWD", &p_env);
	pwd = ft_strjoin_f("OLDPWD=", pwd, 2);
	final_old_pwd = ft_strjoin("PWD=", (old_pwd) ? old_pwd : "");
	ft_export_declare(env, pwd, true, true);
	ft_export_declare(env, final_old_pwd, true, true);
	chdir(old_pwd);
	ft_strdel(&pwd);
	ft_strdel(&old_pwd);
	ft_strdel(&final_old_pwd);
	return (1);
}
