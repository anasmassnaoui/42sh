/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:25:29 by aariss            #+#    #+#             */
/*   Updated: 2020/01/26 19:25:32 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	display_error(int fd)
{
	char	*itoa;

	itoa = error_assembly(fd);
	ft_putendl_fd(itoa, 2);
	ft_strdel(&itoa);
}

int		aggregation_fd(t_info *lst, t_bool def)
{
	int		fds;

	if (def == true)
	{
		fds = (lst->sfd != -2)
			? dup2(lst->dfd, lst->sfd) : dup2(lst->dfd, 1);
		if (fds == -1)
		{
			display_error(lst->dfd);
			return (0);
		}
	}
	else
	{
		if (lst->sfd != -2)
			close(lst->sfd);
		else
			close(1);
	}
	return (1);
}
