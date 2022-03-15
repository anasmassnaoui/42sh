/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flags1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:44:27 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/17 12:11:10 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "readline.h"

int				check_flags1(char *ptr)
{
	if (!ft_strcmp(ptr, "-s") || !ft_strcmp(ptr, "-l")
	|| (!ft_strcmp(ptr, "-ln")) || !ft_strcmp(ptr, "-lr")
	|| !ft_strcmp(ptr, "-lnr") || !ft_strcmp(ptr, "-lrn"))
		return (1);
	else
		return (0);
}

void			flags_e_one_arg(t_history *tmp, char **str,
char **tab_env, char **ptr)
{
	if (!which_one(tmp, ptr[3]))
	{
		ft_putendl("42sh: fc: history specification out of range");
		*str = ft_strdup("");
	}
	else
		fc_e(ptr[2], str, tab_env, search_in_hist(tmp,
					ptr[3], ft_atoi(ptr[3])));
}

char			*flags_e_args(t_history *tmp, char **ptr,
char **tab_env, t_history *cmd)
{
	char		*str;

	if (!ft_strcmp(ptr[1], "-re"))
		str = fc_e_args(cmd, ptr, cmd, tab_env);
	else
		str = fc_e_args(tmp, ptr, cmd, tab_env);
	if (!(str))
	{
		ft_putendl("42sh: fc: history specification out of range");
		str = ft_strdup("");
	}
	return (str);
}

void			flags1(char **str, t_history *tmp, char **ptr)
{
	t_history	*hist_tmp;
	t_history	*cmd;
	char		*tmp2;
	int			t;

	t = 0;
	hist_tmp = tmp;
	cmd = reverse_lst(copy_lst(hist_tmp));
	tmp2 = *str;
	if (ptr[1] == NULL)
		ft_putendl("fc: not enough arguments");
	else if (!ft_strcmp(ptr[1], "-s"))
	{
		*str = fc_s_one(tmp, ptr);
		ft_strdel(&tmp2);
	}
	else if (!ft_strcmp(ptr[1], "-l") || (!ft_strcmp(ptr[1], "-ln")))
		fc_ln_one(tmp, t, ptr, cmd);
	else if (!ft_strcmp(ptr[1], "-lr") || (!ft_strcmp(ptr[1], "-lnr"))
			|| (!ft_strcmp(ptr[1], "-lrn")))
		fc_reverse(t, ptr, cmd);
	if (cmd)
		free_list_hist(&cmd);
}

void			flags_e(t_history *tmp, char **ptr, char **str, char **tab_env)
{
	t_history	*hist_tmp;
	t_history	*cmd;

	hist_tmp = tmp;
	cmd = reverse_lst(copy_lst(hist_tmp));
	if (!ft_strcmp(ptr[1], "-r") && ptr[2] == NULL)
		r_in_file(tab_env, last_node(tmp));
	else if (ptr[2] == NULL)
	{
		ft_putendl("42sh: fc: option requires an argument");
		free_list_hist(&cmd);
		return ;
	}
	else if (!ft_strcmp(ptr[2], "-") && ptr[3] == NULL)
		*str = last_node(tmp);
	else if (!check_editor(ptr[2]))
		*str = ft_strdup(ptr[2]);
	else if (check_editor(ptr[2]) && ptr[3] == NULL)
		fc_e(ptr[2], str, tab_env, last_node(tmp));
	else if (check_editor(ptr[2]) && ptr[3] != NULL && ptr[4] == NULL)
		flags_e_one_arg(tmp, str, tab_env, ptr);
	else
		*str = flags_e_args(tmp, ptr, tab_env, cmd);
	free_list_hist(&cmd);
}
