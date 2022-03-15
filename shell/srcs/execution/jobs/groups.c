/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:31:35 by amassnao          #+#    #+#             */
/*   Updated: 2020/01/31 22:12:02 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	group_up(t_group *group, int current)
{
	t_bool lock_0;
	t_bool lock_1;

	lock_0 = false;
	lock_1 = false;
	if (current == -1)
		return ;
	while (group)
	{
		if (current == 1 && group->current == 0 && !lock_1)
		{
			group->current = 1;
			lock_1 = true;
		}
		if ((current == 0 || current == 1) && group->current == -1 && !lock_0)
		{
			group->current = 0;
			lock_0 = true;
		}
		group = group->next;
	}
}

void	group_down(t_group *group)
{
	if (!group)
		return ;
	group_down(group->next);
	if (group->current == 1)
		group->current = 0;
	else if (group->current == 0)
		group->current = -1;
}

void	create_group(t_holder *h, pid_t pgid, char *cmd)
{
	t_group *group;

	group = (t_group *)malloc(sizeof(t_group));
	group->pgid = pgid;
	group->cmd = ft_strdup(cmd);
	group->process = NULL;
	group->current = 1;
	if (h->background)
	{
		if (h->groups && h->groups->next)
			group->current = -1;
		else if (h->groups)
			group->current = 0;
		else
			group_down(h->groups);
	}
	else
		group_down(h->groups);
	group->suspend = false;
	group->next = h->groups;
	group->id = (h->groups) ? h->groups->id + 1 : 1;
	h->groups = group;
}

void	join_group(t_group *group, pid_t pid, t_bool suspend, char *cmd)
{
	t_process	*process;
	t_holder	*h;

	process = (t_process *)malloc(sizeof(t_process));
	h = get_set_holder(false, NULL);
	process->pid = pid;
	process->suspend = suspend;
	process->cmd = ft_strdup(cmd);
	process->next = group->process;
	if (suspend && group->process == NULL)
	{
		ft_putstr_fd("[", get_set_holder(false, NULL)->fd);
		ft_putnbr_fd(group->id, get_set_holder(false, NULL)->fd);
		ft_putstr_fd("] ", get_set_holder(false, NULL)->fd);
		ft_putnbr_fd(pid, get_set_holder(false, NULL)->fd);
		ft_putendl_fd("", get_set_holder(false, NULL)->fd);
	}
	group->process = process;
}

void	delete_group(t_holder *h, t_group *prev, t_group *node, pid_t pgid)
{
	if (!node)
		return ;
	if (node->pgid == pgid)
	{
		if (!prev)
			h->groups = node->next;
		else
			prev->next = node->next;
		group_up(h->groups, node->current);
		free(node->cmd);
		free(node);
		return ;
	}
	delete_group(h, node, node->next, pgid);
}
