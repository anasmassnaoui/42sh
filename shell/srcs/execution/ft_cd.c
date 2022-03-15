/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 20:43:03 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 20:43:03 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*chdir_or_errno(t_stat buf, char **cmd, int flag, t_env *env)
{
	char	*tmp;
	char	*final_path;

	tmp = get_var("PWD", &env);
	final_path = assemble_path(tmp, cmd[flag]);
	if (ft_strlen(final_path) == 0)
	{
		ft_strdel(&final_path);
		final_path = ft_strdup("/");
	}
	if (access(final_path, X_OK) == 0)
	{
		chdir(final_path);
		return (final_path);
	}
	if (S_ISDIR(buf.st_mode) && access(cmd[flag], X_OK) != 0)
		chdir_gerror(cmd[flag], 1);
	else if (!S_ISDIR(buf.st_mode))
		chdir_gerror(cmd[flag], 0);
	return (NULL);
}

char	*chdir_path(t_holder *h, int flag, int *t)
{
	char	**cmd;
	t_stat	buffer;

	cmd = h->lst->cmd;
	lstat(cmd[flag], &buffer);
	if (ft_strcmp(cmd[1], "-") == 0 && (*t = 1))
	{
		swap_paths(&h->head_ref);
		return (getcwd(NULL, 0));
	}
	else
	{
		if (access(cmd[flag], F_OK) == 0)
			return (chdir_or_errno(buffer, cmd, flag, h->head_ref));
		else
			chdir_gerror(cmd[1], 2);
	}
	return (NULL);
}

char	*cd_handler(t_holder *h, int count_args, int *t)
{
	char	*new_dir_path;

	new_dir_path = NULL;
	if (count_args == 3 && is_flag(h->lst->cmd[1]))
	{
		if (!(new_dir_path = cd_with_flag(h, new_dir_path)))
			return (NULL);
	}
	else if (count_args == 2)
	{
		if (!(new_dir_path = chdir_path(h, 1, t)))
			return (NULL);
	}
	else
	{
		ft_putendl_fd("42sh cd: too many arguments", 2);
		return (NULL);
	}
	return (new_dir_path);
}

void	free_dir_path(char *new, char *current)
{
	ft_strdel(&new);
	ft_strdel(&current);
}

int		ft_cd(t_holder *h)
{
	int		t;
	int		count_args;
	char	*new_dir_path;
	char	*current_dir_path;

	t = 0;
	h->lst->cmd = rip_quotes(h->lst->cmd);
	count_args = count_tab(h->lst->cmd);
	current_dir_path = current_dir_manager(h);
	if (count_args == 1 || (count_args == 2 && (!L_CHECK || !P_CHECK)))
	{
		if (!((new_dir_path) = get_var("HOME", &h->head_ref)))
			return (0);
		chdir(new_dir_path);
	}
	else if (!(new_dir_path = cd_handler(h, count_args, &t)))
	{
		ft_strdel(&current_dir_path);
		return (0);
	}
	if (t)
		free_dir_path(new_dir_path, current_dir_path);
	if (!t)
		update_env(new_dir_path, current_dir_path, &h->head_ref);
	return (1);
}
