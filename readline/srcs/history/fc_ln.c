/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 13:27:50 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/28 20:25:24 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void			p_lst(t_history *tmp, int t)
{
	while (tmp)
	{
		ft_putstr("  ");
		if (t == 1)
		{
			ft_putnbr(tmp->nb);
			ft_putstr(" ");
		}
		ft_putendl(tmp->history);
		tmp = tmp->next;
	}
}

void			print_index(t_history *tmp, int t, int index)
{
	int			len;

	len = len_list(tmp);
	if (index < 1)
		index = 1;
	while (tmp)
	{
		if (index > len)
		{
			if (t == 1)
				ft_putnbr(len);
			ft_putstr("  ");
			ft_putendl(last_node(tmp));
			return ;
		}
		else if (index == tmp->nb)
		{
			p_lst(tmp, t);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void			p_range(t_history *lst, int start, int end, int t)
{
	while (lst)
	{
		if (lst->nb >= start && lst->nb <= end)
		{
			ft_putstr("  ");
			if (t == 1)
			{
				ft_putnbr((lst)->nb);
				ft_putstr(" ");
			}
			ft_putendl((lst)->history);
			lst = lst->next;
		}
		else
			lst = lst->next;
	}
}

void			one_arg_ln(t_history *tmp, int t, char **ptr, t_history *cmd)
{
	if (ptr[2] && ptr[3] == NULL)
	{
		if (ft_atoi(ptr[2]))
			print_index(tmp, t, ft_atoi(ptr[2]));
		else
		{
			if (hist_index(cmd, ptr[2]))
				print_index(tmp, t, hist_index(cmd, ptr[2]));
			else
				ft_putendl("42sh: fc: history specification out of range");
		}
	}
}

void			many_args_ln(t_history *tmp, int t, char **ptr, t_history *cmd)
{
	int			a;
	int			b;

	if (which_one(cmd, ptr[2]) && which_one(cmd, ptr[3]))
	{
		a = which_one(cmd, ptr[2]);
		b = which_one(cmd, ptr[3]);
		if (a < b)
			p_range(tmp, a, b, t);
		else if (a > b)
			p_range(cmd, b, a, t);
	}
	else
		ft_putendl("42sh: fc: history specification out of range");
}
