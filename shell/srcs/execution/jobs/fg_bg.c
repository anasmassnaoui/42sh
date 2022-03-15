/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:57:25 by aariss            #+#    #+#             */
/*   Updated: 2020/01/21 13:58:30 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		fg_handler(t_holder *h, char *args)
{
	int status;

	status = 0;
	if (!ft_strncmp(args, "%%", 2))
	{
		if (!h->groups || (h->groups
					&& !resume_group_fg(h, h->groups, valid_id(args))))
			status = show_jobs_msg("fg", args);
	}
	else if (!valid_id(args))
		status = show_jobs_msg("fg", args);
	else if (valid_id(args) && !resume_group_fg(h, h->groups, valid_id(args)))
		status = show_jobs_msg("fg", args);
	return (status);
}

int		fg(t_holder *h, char **args)
{
	int status;

	status = 0;
	if (check_flag(args, "fg: -", "fg: usage: fg [jobspec]", false) < 0)
		return (1);
	if (!h->groups && !args[1])
	{
		ft_putendl_fd("fg: current: no such job", 2);
		status = 1;
	}
	else if (h->groups && !args[1])
		status = resume_group_fg(h, h->groups, 0);
	else
		status = fg_handler(h, args[1]);
	return (status);
}

int		bg_handler(t_holder *h, char **args, int status)
{
	if (!*args)
		return (status);
	if (!ft_strncmp(*args, "%%", 2))
	{
		if (!h->groups
				|| (h->groups
					&& !resume_group_bg(h, h->groups, valid_id(*args))))
			status = show_jobs_msg("bg", *args);
	}
	else if (!valid_id(*args))
		status = show_jobs_msg("bg", *args);
	else if (valid_id(*args) && !resume_group_bg(h, h->groups, valid_id(*args)))
		status = show_jobs_msg("bg", *args);
	return (bg_handler(h, args + 1, status));
}

int		bg(t_holder *h, char **args)
{
	int status;

	status = 0;
	if (check_flag(args, "bg: -", "bg: usage: bg [jobspec ...]", false) < 0)
		return (1);
	if (!h->groups && !args[1])
	{
		ft_putendl_fd("bg: current: no such job", 2);
		status = 1;
	}
	else if (h->groups && !args[1])
		resume_group_bg(h, h->groups, 0);
	else
		bg_handler(h, args + 1, 0);
	return (status);
}
