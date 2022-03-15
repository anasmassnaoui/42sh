/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 12:43:03 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/14 18:01:47 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				check_editor(char *ptr)
{
	if (!ft_strcmp(ptr, "vim") || !ft_strcmp(ptr, "nano")
			|| !ft_strcmp(ptr, "emacs"))
		return (1);
	return (0);
}

void			err_msg(char **ptr)
{
	if (ptr[1][0] == '-')
		return ;
	else
		ft_putendl("42sh: fc: history specification out of range");
}

int				check_jobs(char **ptr)
{
	int			i;

	i = 0;
	while (ptr[i])
	{
		if (!ft_strcmp(ptr[i], "&"))
			return (1);
		i++;
	}
	return (0);
}

void			fc_exec(t_history *tmp, char **ptr, char **str, char **tab_env)
{
	char		*tmp2;

	tmp2 = *str;
	if (check_jobs(ptr))
		return ;
	flags_e(tmp, ptr, str, tab_env);
	if (ptr[2])
		ft_strdel(&tmp2);
}

void			fc_command(char **str, char **cmd,
		t_all_hist *history, char **tab_env)
{
	char		**ptr;
	t_history	*tmp;

	ptr = cmd;
	if (!ft_strcmp(ptr[0], "fc") && (tmp = history->lst))
	{
		if (ptr[1] == NULL && (history->x = 1))
			r_in_file(tab_env, last_node(tmp));
		else if (!check_flags(ptr[1]) && !check_flags1(ptr[1]))
			fc_no_flags(tmp, ptr, str, tab_env);
		else if (check_flags1(ptr[1]))
			flags1(str, tmp, ptr);
		else if (!ft_strcmp(ptr[1], "-e")
		|| !ft_strcmp(ptr[1], "-re") || !ft_strcmp(ptr[1], "-r"))
			fc_exec(tmp, ptr, str, tab_env);
		else
			err_msg(ptr);
	}
}
