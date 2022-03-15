/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:51:26 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 12:51:42 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	group_state(t_group *group, pid_t pgid)
{
	while (group)
	{
		if (group->pgid == pgid)
			group->current = 1;
		else if (group->pgid != pgid && group->current == 1)
			group->current = 0;
		else
			group->current = -1;
		group = group->next;
	}
}

void	show_messages(t_message *message)
{
	if (!message)
		return ;
	show_messages(message->next);
	if (message->message)
		ft_putendl_fd(message->message, get_set_holder(false, NULL)->fd);
	free(message->message);
	free(message);
}

int		groups_ids(t_group *group, int start_id)
{
	int id;

	if (!group)
		return (start_id);
	id = groups_ids(group->next, start_id);
	group->id = id;
	return (id + 1);
}

void	monitor_groups(t_holder *h)
{
	t_group *group;
	t_group *next;

	group = h->groups;
	while (group)
	{
		next = group->next;
		monitor_process(group, group->process, false, false);
		group->suspend = false;
		if (!group->process)
			delete_group(h, NULL, h->groups, group->pgid);
		group = next;
	}
}
