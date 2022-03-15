/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 13:39:08 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/08 18:04:12 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void			p_history(t_history **hist, int t)
{
	while (*hist)
	{
		ft_putstr("  ");
		if (t == 1)
		{
			ft_putnbr((*hist)->nb);
			ft_putstr(" ");
		}
		ft_putendl((*hist)->history);
		*hist = (*hist)->next;
	}
}

void			print_history(t_history *lst, int t)
{
	t_history	*hist;
	int			start;
	int			i;

	start = len_list(lst) - 16;
	i = 0;
	hist = lst;
	while (hist)
	{
		if (len_list(lst) > 16)
		{
			if (i == start)
				p_history(&hist, t);
			else
				hist = hist->next;
			i++;
		}
		else
			p_history(&hist, t);
	}
}
