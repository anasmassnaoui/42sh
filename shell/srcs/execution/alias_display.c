/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:47:20 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:47:22 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_one_alias(t_holder *h, t_alias *aliases)
{
	while (aliases)
	{
		if (!ft_strcmp(aliases->alias, h->lst->cmd[1]))
		{
			ft_putstr("alias ");
			ft_putstr(aliases->alias);
			ft_putstr("=\"");
			ft_putstr(aliases->original);
			ft_putendl("\"");
			return (1);
		}
		aliases = aliases->next;
	}
	return (0);
}

void	list_aliases(t_alias *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		ft_putstr("alias ");
		ft_putstr(lst->alias);
		ft_putstr("=\"");
		ft_putstr(lst->original);
		ft_putendl("\"");
		lst = lst->next;
	}
}
