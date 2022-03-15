/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_ln_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 20:56:45 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/04 14:51:49 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void			p_reverse(t_history *lst, int t)
{
	int			i;

	i = 0;
	while (lst && i < 16)
	{
		ft_putstr("  ");
		if (t == 1)
		{
			ft_putnbr(lst->nb);
			ft_putstr(" ");
		}
		ft_putendl(lst->history);
		lst = lst->next;
		i++;
	}
}

void			p_nb(t_history *cmd_tmp, int t)
{
	if (t == 1)
	{
		ft_putnbr(cmd_tmp->nb);
		ft_putstr(" ");
	}
}

void			rev_one_varb(t_history *cmd_tmp, char *ptr, int t)
{
	while (cmd_tmp)
	{
		if (!ft_strncmp(cmd_tmp->history, ptr, ft_strlen(ptr)))
		{
			ft_putstr("  ");
			p_nb(cmd_tmp, t);
			ft_putendl(cmd_tmp->history);
			return ;
		}
		else
		{
			ft_putstr("  ");
			p_nb(cmd_tmp, t);
			ft_putendl(cmd_tmp->history);
		}
		cmd_tmp = cmd_tmp->next;
	}
}

void			p_rev_index(t_history *cmd_tmp, int index, int t)
{
	int			i;

	i = 0;
	if (index > len_list(cmd_tmp))
	{
		ft_putstr("  ");
		p_nb(cmd_tmp, t);
		ft_putendl(cmd_tmp->history);
		return ;
	}
	while (cmd_tmp && cmd_tmp->nb >= index)
	{
		ft_putstr("  ");
		p_nb(cmd_tmp, t);
		ft_putendl(cmd_tmp->history);
		cmd_tmp = cmd_tmp->next;
		i++;
	}
}

void			reverse_one_arg(char *ptr, t_history *cmd, int t)
{
	t_history	*cmd_tmp;

	cmd_tmp = cmd;
	if (ft_atoi(ptr))
		p_rev_index(cmd_tmp, ft_atoi(ptr), t);
	else
	{
		if (hist_index(cmd_tmp, ptr))
			rev_one_varb(cmd_tmp, ptr, t);
		else
			ft_putendl("42sh: fc: history specification out of range");
	}
}
