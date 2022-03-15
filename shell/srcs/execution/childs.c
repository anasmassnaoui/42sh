/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:24:18 by aariss            #+#    #+#             */
/*   Updated: 2020/02/06 23:35:51 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		free_child(t_childs *lst)
{
	if (lst == NULL)
		return ;
	free_child(lst->next);
	free(lst);
	lst = NULL;
}

int			kill_pid(t_holder *h, int *keeper, int status)
{
	cheap_trick(keeper, 1);
	if (status != -1)
		return (status);
	if (!h->current_groupe)
		return (2);
	if (!h->background)
	{
		status = monitor_process(h->current_groupe,
			h->current_groupe->process, true, false);
		if (!h->current_groupe->process && h->pid_42sh)
		{
			delete_group(h, NULL, h->groups, h->current_groupe->pgid);
			h->current_groupe = NULL;
		}
		if (h->pid_42sh)
		{
			ft_tcsetpgrp(0, h->pid_42sh);
			monitor_groups(h);
		}
	}
	else
		status = 0;
	return (status);
}

t_childs	*create_child(pid_t child_pid, int *t, int def)
{
	t_childs *new;

	if (!(new = (t_childs*)malloc(sizeof(t_childs))))
		return (0);
	new->child = child_pid;
	new->index = def;
	new->next = NULL;
	(*t)++;
	return (new);
}
