/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:55:20 by amassnao          #+#    #+#             */
/*   Updated: 2020/02/10 23:58:34 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

t__mc		*type_command_handler(t__mc *current, t_holder *h)
{
	pid_t child_pid;

	if (is_aand_oor_exist(current) && is_and_exit(current))
	{
		if ((child_pid = fork()) == 0)
		{
			default_signal();
			child_pid = getpid();
			setpgid(child_pid, child_pid);
			create_group(h, child_pid, h->line);
			h->current_groupe = h->groups;
			h->pid_42sh = 0;
			and_or_handler(h, current, true, true);
		}
		setpgid(child_pid, child_pid);
		create_group(h, child_pid, h->line);
		join_group(h->groups, child_pid, true, h->line);
		current = and_or_handler(h, current, false, false);
	}
	else if (is_and_exit(current) && (h->background = true))
		current = and_or_handler(h, current, true, false);
	else
		current = and_or_handler(h, current, true, false);
	return (current);
}

void		command_handler(t_holder *h, t_bool same_group)
{
	int		commands_status;
	t__mc	*current;
	t__mc	*tmp;

	current = h->mclst;
	commands_status = -1;
	signal(SIGCHLD, SIG_DFL);
	while (current)
	{
		h->background = false;
		if (!same_group)
			h->current_groupe = NULL;
		if (current->def == 4 || current->def == 3)
		{
			commands_status = -1;
			current = current->next;
			continue ;
		}
		tmp = current;
		current = type_command_handler(current, h);
	}
	signal(SIGCHLD, process_signal);
}

t_bool		is_and_exit(t__mc *root)
{
	if (!root || (root && root->def == 4))
		return (false);
	if (root->def == 3)
		return (true);
	return (is_and_exit(root->next));
}

t_bool		is_aand_oor_exist(t__mc *root)
{
	if (!root || (root && root->def == 4))
		return (false);
	if (root->def == 1 || root->def == 2)
		return (true);
	return (is_aand_oor_exist(root->next));
}

t__mc		*and_or_handler(t_holder *h, t__mc *group,
	t_bool execute, t_bool exit_after)
{
	int commands_status;

	commands_status = -1;
	while (group && group->def != 3 && group->def != 4)
	{
		if (execute && is_operator(group->def))
		{
			if (group->def == 1 && commands_status)
				group = group->next;
			if (group->def == 2 && !commands_status)
				group = group->next;
			group = group->next;
			continue ;
		}
		(execute) ? h->current_mclst = group : 0;
		(execute) ? commands_status = eval_command(h, group->cmd) : 0;
		group = group->next;
	}
	if (exit_after)
		exit(WEXITSTATUS(commands_status));
	if (!exit_after && execute)
		h->last_status = WEXITSTATUS(commands_status);
	return (group);
}
