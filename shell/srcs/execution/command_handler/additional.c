/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 19:21:58 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 15:37:40 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

t_holder	*get_set_holder(t_bool set, t_holder **h)
{
	static t_holder *holder;

	if (set)
		holder = *h;
	return (holder);
}

void		prepare_shell(t_holder **h, char **environ)
{
	pid_t pid;

	set_signals();
	if (isatty(0))
		while (ft_tcgetpgrp(0) != (pid = getpgrp()))
			kill(pid, SIGSTOP);
	else
		(*h)->interactive = true;
	pid = getpid();
	setpgid(pid, pid);
	ft_tcsetpgrp(0, pid);
	(*h)->head_ref = copy_of_env(environ);
	(*h)->tmp_env = NULL;
	(*h)->hash.count = 0;
	(*h)->hash.size = SIZE_HASH;
	(*h)->groups = NULL;
	(*h)->background = false;
	(*h)->force_exit = false;
	(*h)->pid_42sh = pid;
	(*h)->current_groupe = NULL;
	(*h)->messages = NULL;
	(*h)->error = NULL;
	(*h)->reset_readline = false;
	(*h)->ctrl_check = false;
	get_set_holder(true, h);
}

t_bool		is_operator(int command)
{
	if (command == 1 || command == 2)
		return (true);
	return (false);
}

t_bool		parse_error_check(t_holder *h)
{
	t__mc		*lst;
	t_cmd		*cmd;

	lst = h->mclst;
	h->test = true;
	while (lst)
	{
		if (lst->def == 0)
		{
			cmd = last_splice(lst->cmd, h->head_ref, h->aliases);
			if (h->error && !ft_strcmp(h->error, "parse_error"))
			{
				ft_strdel(&h->error);
				free_main_lst(cmd);
				return (false);
			}
			free_main_lst(cmd);
		}
		else if ((lst->def == 1 || lst->def == 2) && lst->next == NULL)
			return (false);
		lst = lst->next;
	}
	h->test = false;
	return (true);
}

void		ft_tcsetpgrp(int fd, pid_t pgid)
{
	ioctl(fd, TIOCSPGRP, &pgid);
}
