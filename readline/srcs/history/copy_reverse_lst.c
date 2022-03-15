/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_reverse_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 13:35:14 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/04 17:21:03 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*copy_lst(t_history *lst)
{
	t_history *new_lst;
	t_history *curr;
	t_history *temp;

	new_lst = NULL;
	curr = lst;
	temp = NULL;
	while (curr)
	{
		if (!new_lst)
		{
			temp = get_history(curr->history);
			temp->nb = curr->nb;
			new_lst = temp;
		}
		else
		{
			temp->next = get_history(curr->history);
			temp = temp->next;
			temp->nb = curr->nb;
		}
		curr = curr->next;
	}
	return (new_lst);
}

t_history	*reverse_lst(t_history *lst)
{
	t_history *prev;
	t_history *current;
	t_history *next;

	prev = NULL;
	current = lst;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	lst = prev;
	return (lst);
}

char		*last_node(t_history *tmp)
{
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp->history);
		tmp = tmp->next;
	}
	return (0);
}
