/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 15:58:24 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/28 20:25:39 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		many_args_reverse(int t, char **ptr, t_history *cmd)
{
	int		a;
	int		b;

	if (which_one(cmd, ptr[2]) && which_one(cmd, ptr[3]))
	{
		a = which_one(cmd, ptr[2]);
		b = which_one(cmd, ptr[3]);
		if (a < b)
			p_range(cmd, a, b, t);
		else if (a > b)
			p_range(cmd, b, a, t);
	}
	else
		ft_putendl("42sh: fc: history specification out of range");
}

void		fc_reverse(int t, char **ptr, t_history *cmd)
{
	if (!ft_strcmp(ptr[1], "-lr"))
		t = 1;
	else
		t = 0;
	if (ptr[2] == NULL)
		p_reverse(cmd, t);
	else if (ptr[3] == NULL)
		reverse_one_arg(ptr[2], cmd, t);
	else
		many_args_reverse(t, ptr, cmd);
}
