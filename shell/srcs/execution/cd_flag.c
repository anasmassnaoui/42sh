/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:35:57 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 22:35:58 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*chdir_with_flag(t_holder *h)
{
	t_stat		buffer;
	char		*link;
	char		**cmd;
	int			t;

	t = 0;
	link = NULL;
	cmd = h->lst->cmd;
	lstat(cmd[2], &buffer);
	if (ft_strcmp(cmd[1], "-P") == 0)
	{
		link = getcwd(NULL, 0);
		ft_strdel(&link);
		chdir(cmd[2]);
		return (getcwd(NULL, 0));
	}
	if (!(link = chdir_path(h, 2, &t)))
		return (NULL);
	return (link);
}

int		is_flag(char *str)
{
	if (ft_strlen(str) == 2 && str[0] == '-')
		return (1);
	return (0);
}

char	*cd_with_flag(t_holder *h, char *new_dir_path)
{
	if (ft_strcmp(h->lst->cmd[1], "-P") == 0
		|| ft_strcmp(h->lst->cmd[1], "-L") == 0)
	{
		if (!(new_dir_path = chdir_with_flag(h)))
			return (NULL);
	}
	else
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(h->lst->cmd[1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
		return (NULL);
	}
	return (new_dir_path);
}
