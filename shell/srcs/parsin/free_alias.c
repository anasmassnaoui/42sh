/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:19:51 by aariss            #+#    #+#             */
/*   Updated: 2020/01/23 19:19:53 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_list_alias(t_alias *head)
{
	t_alias	*current;

	current = head;
	while (head)
	{
		current = head;
		head = head->next;
		ft_strdel(&current->alias);
		ft_strdel(&current->original);
		free(current);
		current = NULL;
	}
}

void	free_alias_vars(char *a, char *b, char *c)
{
	ft_strdel(&a);
	ft_strdel(&b);
	ft_strdel(&c);
}
