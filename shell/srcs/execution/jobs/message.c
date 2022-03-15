/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:36:49 by amassnao          #+#    #+#             */
/*   Updated: 2020/01/27 18:36:53 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*create_message(t_group *group, t_process *process, char *msg)
{
	msg = ft_strjoin_f("[", ft_itoa(group->id), 2);
	(group->current == 1) ? msg = ft_strjoin_f(msg, "]+ ", 1) : 0;
	(group->current == 0) ? msg = ft_strjoin_f(msg, "]- ", 1) : 0;
	if (group->current < 0)
		msg = ft_strjoin_f(msg, "] ", 1);
	msg = (WIFSTOPPED(process->status)) ? msg :
		ft_strjoin_f(msg, ft_itoa(process->pid), 3);
	if (WIFEXITED(process->status) && !process->status)
		msg = ft_strjoin_f(msg, " Done", 1);
	if (WIFSTOPPED(process->status))
		msg = ft_strjoin_f(msg, " Stopped ", 1);
	if ((WIFEXITED(process->status) && process->status))
	{
		msg = ft_strjoin_f(msg, " Exit ", 1);
		msg = ft_strjoin_f(msg, ft_itoa(WEXITSTATUS(process->status)), 3);
	}
	if (WIFSIGNALED(process->status))
	{
		msg = ft_strjoin_f(msg, " ", 1);
		msg = ft_strjoin_f(msg, ft_strsignal(WTERMSIG(process->status)), 1);
		msg = ft_strjoin_f(msg, ": ", 1);
		msg = ft_strjoin_f(msg, ft_itoa(WTERMSIG(process->status)), 3);
	}
	msg = ft_strjoin_f(msg, " ", 1);
	return (ft_strjoin_f(msg, process->cmd, 1));
}

void	add_message(t_group *group, t_process *process, t_bool suspend)
{
	t_message	*msg;
	t_holder	*h;

	if (!suspend && ((WIFSIGNALED(process->status)
					&& (WTERMSIG(process->status) == 2
						|| WTERMSIG(process->status) == 13))
				|| WIFEXITED(process->status)))
		return ;
	msg = (t_message *)malloc(sizeof(t_message));
	msg->message = create_message(group, process, "msg");
	h = get_set_holder(false, NULL);
	msg->next = h->messages;
	h->messages = msg;
}
