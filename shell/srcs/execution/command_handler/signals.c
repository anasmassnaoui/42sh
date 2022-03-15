/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:56:25 by amassnao          #+#    #+#             */
/*   Updated: 2020/01/27 18:56:27 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void		process_signal(int sig)
{
	t_holder *h;

	(void)sig;
	h = get_set_holder(false, NULL);
	monitor_groups(h);
}

void		re_read(int sig)
{
	(void)sig;
	if (!get_set_holder(false, 0)->ctrl_check)
	{
		ft_putstr(COLOR2);
		ft_putstr("\n$> ");
		write(1, tgetstr("cd", NULL), ft_strlen(tgetstr("cd", NULL)));
		ft_putstr_fd(RESET2, 1);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ioctl(0, TIOCSTI, "\n");
		get_set_holder(false, 0)->ctrl_check = false;
	}
	get_set_holder(false, 0)->reset_readline = true;
}

void		set_signals(void)
{
	signal(SIGINT, re_read);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, process_signal);
}

void		default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
