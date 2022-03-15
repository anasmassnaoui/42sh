/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extention.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:53:21 by aariss            #+#    #+#             */
/*   Updated: 2020/01/26 10:53:23 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*right_path(char **tableau, char *arg)
{
	char	*tmp;
	char	*temp;
	char	*res;
	int		i;

	tmp = ft_strjoin("/", arg);
	i = -1;
	res = NULL;
	while (tableau[++i])
	{
		temp = arg;
		(arg = ft_strjoin(tableau[i], tmp)) ? ft_strdel(&temp) : 0;
		if (access(arg, F_OK) == 0)
		{
			res = arg;
			break ;
		}
		ft_strdel(&arg);
	}
	ft_free2d(tableau);
	ft_strdel(&tmp);
	return (res);
}

char	*verify_env(char *arg, t_env **head_ref)
{
	char	**tableau;
	char	*res;

	res = NULL;
	if (ft_strncmp(arg, "./", 2) != 0)
	{
		if (!(tableau = get_path(head_ref)))
		{
			path_gestion_error(arg);
			return (0);
		}
		res = right_path(tableau, arg);
	}
	return (res);
}

int		which_and_del(t_holder *h, int j)
{
	int		i;
	t_bool	lock;

	lock = false;
	i = 1;
	while (h->lst->cmd[i])
	{
		if (!lock && !ft_strncmp(h->lst->cmd[i], "-", 1))
		{
			(j == 4) ? ft_putstr("unset: ") : 0;
			(j == 6) ? ft_putstr("which: ") : 0;
			ft_putstr(h->lst->cmd[i]);
			ft_putendl(": invalid option");
			(j == 4) ? ft_putendl("usage: unset [name ...]") : 0;
			(j == 6) ? ft_putendl("usage: which program ...") : 0;
			return (2);
		}
		if (j == 4)
			del_node(h->lst->cmd[i], &h->head_ref);
		else if (j == 6)
			which_cmd(h->lst->cmd[i], &h->head_ref);
		lock = true;
		i++;
	}
	return (0);
}

int		hash_manager(t_holder *h, int i)
{
	char	*tmp;
	char	*arg;
	int		status;

	arg = ft_strdup(h->lst->cmd[i]);
	tmp = verify_env(arg, &h->head_ref);
	status = hash_flags(&h->hash, h->lst->cmd[i], h->lst->cmd[i + 1], tmp);
	return (status);
}
