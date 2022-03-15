/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:29:07 by amassnao          #+#    #+#             */
/*   Updated: 2020/02/10 23:38:40 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	group_continue(t_group *group)
{
	t_process *process;

	process = group->process;
	while (process)
	{
		process->suspend = false;
		process = process->next;
	}
}

t_bool	resume_group_fg(t_holder *h, t_group *group, int id)
{
	if (!group)
		return (false);
	if (resume_group_fg(h, group->next, id))
		return (true);
	if (group->id == id || (id == 0 && group->current == 1))
	{
		ft_putstr_fd("[", get_set_holder(false, NULL)->fd);
		ft_putnbr_fd(group->id, get_set_holder(false, NULL)->fd);
		ft_putstr_fd("]+ Continued ", get_set_holder(false, NULL)->fd);
		ft_putendl_fd(group->cmd, get_set_holder(false, NULL)->fd);
		group_continue(group);
		if (group->current != 1)
			group_state(h->groups, group->pgid);
		ft_tcsetpgrp(0, group->pgid);
		killpg(group->pgid, SIGCONT);
		signal(SIGCHLD, SIG_DFL);
		group->suspend = false;
		monitor_process(group, group->process, true, false);
		(!group->process) ? delete_group(h, NULL, h->groups, group->pgid) : 0;
		(!group->process) ? h->current_groupe = NULL : 0;
		ft_tcsetpgrp(0, h->pid_42sh);
		signal(SIGCHLD, process_signal);
		return (true);
	}
	return (false);
}

t_bool	resume_group_bg(t_holder *h, t_group *group, int id)
{
	if (!group)
		return (false);
	if (resume_group_bg(h, group->next, id))
		return (true);
	if (group->id == id || (id == 0 && group->current == 1))
	{
		ft_putstr_fd("[", get_set_holder(false, NULL)->fd);
		ft_putnbr_fd(group->id, get_set_holder(false, NULL)->fd);
		ft_putstr_fd("]  Continued ", get_set_holder(false, NULL)->fd);
		ft_putendl_fd(group->cmd, get_set_holder(false, NULL)->fd);
		ft_tcsetpgrp(0, h->pid_42sh);
		killpg(group->pgid, SIGCONT);
		group->suspend = false;
		monitor_process(group, group->process, false, true);
		return (true);
	}
	return (false);
}

t_bool	show_groups(t_group *group, int id, int flag)
{
	if (!group && !id)
		return (true);
	if (!group)
		return (false);
	if (id && id != group->id)
		return (show_groups(group->next, id, flag));
	(!id) ? show_groups(group->next, id, flag) : 0;
	(flag == 0 || flag == 1) ? ft_putstr_fd("[", 1) : 0;
	(flag == 0 || flag == 1) ? ft_putnbr_fd(group->id, 1) : 0;
	(flag == 0 || flag == 1) ? ft_putstr_fd("]", 1) : 0;
	(flag == 2) ? ft_putnbr_fd(group->pgid, 1) : 0;
	((group->current == 1) && (flag == 0 || flag == 1)) ?
	ft_putstr_fd("+ ", 1) : 0;
	((group->current == 0) && (flag == 0 || flag == 1)) ?
	ft_putstr_fd("- ", 1) : 0;
	((group->current < 0) && (flag == 0 || flag == 1)) ?
	ft_putstr_fd("  ", 1) : 0;
	(flag == 1) ? show_process(group->process) : 0;
	(flag == 0 && is_process_suspended(group->process)) ?
	ft_putstr_fd("Stopped ", 1) : 0;
	(flag == 0 && !is_process_suspended(group->process)) ?
	ft_putstr_fd("Running ", 1) : 0;
	(flag == 0) ? ft_putendl_fd(group->cmd, 1) : 0;
	(flag == 2) ? ft_putendl_fd("", 1) : 0;
	return (true);
}

int		valid_id(char *id)
{
	char *p;

	if (!id)
		return (false);
	while (*id)
		if (*id == '%' || *id == '#')
			id++;
		else
			break ;
	p = id;
	while (*id)
		if (!ft_isdigit(*id++))
			return (false);
		else
			break ;
	return (ft_atoi(p));
}
