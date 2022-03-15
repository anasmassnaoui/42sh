/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:37:26 by amassnao          #+#    #+#             */
/*   Updated: 2020/02/06 23:35:59 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	show_process(t_process *process)
{
	if (!process)
		return ;
	show_process(process->next);
	if (process->next)
		ft_putstr("     ");
	ft_putnbr(process->pid);
	if (WIFSTOPPED(process->status))
		ft_putstr(" Suspended: 18");
	else
		ft_putstr(" Running");
	ft_putstr("\t");
	ft_putendl(process->cmd);
}

void	delete_process(t_group *group, t_process *prev, t_process *node,
pid_t pid)
{
	if (!node)
		return ;
	if (node->pid == pid)
	{
		if (!prev)
			group->process = node->next;
		else
			prev->next = node->next;
		add_message(group, node, node->suspend);
		free(node->cmd);
		free(node);
		return ;
	}
	if (node->next)
		delete_process(group, node, node->next, pid);
}

int		monitor_process(t_group *group, t_process *process,
t_bool wait_res, t_bool status_anyway)
{
	t_bool	is_changed;
	int		status;

	if (!process)
		return (2);
	is_changed = process_status(process, wait_res, status_anyway);
	status = process->status;
	if (process->next)
		monitor_process(group, process->next, wait_res, status_anyway);
	if (is_changed && !status_anyway)
	{
		if (WIFSTOPPED(process->status))
		{
			if (!group->suspend)
			{
				add_message(group, process, true);
				group->suspend = true;
			}
			process->suspend = true;
		}
		if (!WIFSTOPPED(process->status))
			delete_process(group, NULL, group->process, process->pid);
	}
	return (status);
}

t_bool	is_process_suspended(t_process *process)
{
	if (!process)
		return (false);
	if (!process->next)
	{
		if (WIFSTOPPED(process->status))
			return (true);
		return (false);
	}
	return (is_process_suspended(process->next));
}

t_bool	process_status(t_process *process, t_bool wait_res,
t_bool status_anyway)
{
	pid_t	wait_pid;
	int		status;

	wait_pid = waitpid(process->pid, &status,
	wait_res ? WUNTRACED : WUNTRACED | WNOHANG);
	if (wait_pid > 0 || status_anyway)
	{
		process->status = status;
		return (true);
	}
	return (false);
}
