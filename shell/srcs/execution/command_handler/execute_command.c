/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:55:55 by amassnao          #+#    #+#             */
/*   Updated: 2020/02/01 13:48:37 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void		command_not_faund(t_holder *h)
{
	ft_putendl_fd(h->error, 2);
	exit(2);
}

void		add_env_tmp(t_env **head_ref, t_list *lst, t_bool global,
t_bool force)
{
	if (!lst)
		return ;
	if (lst->next)
		add_env_tmp(head_ref, lst->next, global, force);
	ft_export_declare(head_ref, lst->content, global, force);
	free(lst->content);
	free(lst);
}

void		child_handler(char *cmd, char **args, char **env, t_holder *h)
{
	pid_t child_pid;

	default_signal();
	if (h->lst && !deathly_hallows(h->lst->red))
		exit(1);
	if (!cmd)
		exit(0);
	h->groups = NULL;
	if (h->fd_0 > 0)
		close(h->fd_0);
	if (h->fd_1 > 0)
		close(h->fd_1);
	child_pid = getpid();
	if (!h->current_groupe)
		setpgid(child_pid, child_pid);
	if (h->error)
		command_not_faund(h);
	else if (is_a_builtin(cmd))
		builtin_cmds(h, own_commands(h->lst->cmd), true);
	else
	{
		execve(cmd, args, env);
		ft_printf("%s: not a binary file!", cmd);
		exit(1);
	}
}

pid_t		execute_handler(char *cmd, char **args, char **env, t_holder *h)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0)
		child_handler(cmd, args, env, h);
	else
	{
		if (!h->current_groupe)
		{
			setpgid(child_pid, child_pid);
			create_group(h, child_pid, h->line);
			h->current_groupe = h->groups;
		}
		else
			setpgid(child_pid, h->current_groupe->pgid);
		join_group(h->current_groupe, child_pid, h->background,
		(cmd) ? cmd : h->line);
		if (!h->background && h->pid_42sh)
			ft_tcsetpgrp(0, child_pid);
	}
	return (child_pid);
}

pid_t		ft_tcgetpgrp(int fields)
{
	pid_t pid;

	ioctl(fields, TIOCGPGRP, &pid);
	return (pid);
}
