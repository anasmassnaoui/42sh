/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_master.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:39:38 by aariss            #+#    #+#             */
/*   Updated: 2020/01/14 15:29:12 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		open_file(t_info *lst)
{
	int			fd;
	struct stat	buff;

	fd = 0;
	buff.st_mode = 0;
	lstat(lst->file, &buff);
	if (S_ISFIFO(buff.st_mode))
		fd = open(lst->file, (lst->read_meth > 0) ? O_WRONLY : O_RDONLY, 0644);
	else if (lst->read_meth != 2 && lst->read_meth > 0)
		fd = open(lst->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (lst->read_meth == 2)
		fd = open(lst->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (lst->read_meth == -2)
		fd = open(lst->file, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(lst->file, 2);
		if (lst->read_meth == -2)
			ft_putendl_fd(": No such file or directory", 2);
		else if (lst->read_meth > 0)
			ft_putendl_fd(": Permission denied", 2);
	}
	return (fd);
}

void	heredoc_broker(int *fds, t_info *lst)
{
	char	*str;
	char	*head;

	pipe(fds);
	dup2(fds[0], 0);
	close(fds[0]);
	str = ft_strdup(lst->file);
	head = str;
	if (str[0] == -8)
	{
		str = kill_one(str + 2, HEREDOC);
		str = ft_strjoin("\n", str);
	}
	else
		str = kill_one(str + 1, HEREDOC);
	ft_putstr_fd(str, fds[1]);
	ft_strdel(&head);
	close(fds[1]);
}

void	redirect_to_file(t_info *lst, int fd)
{
	int	fds[2];

	if (lst->read_meth == 1 || lst->read_meth == 2)
	{
		(lst->sfd != -2) ? dup2(fd, lst->sfd) : dup2(fd, 1);
		(fd != lst->sfd) ? close(fd) : 0;
	}
	else if (lst->read_meth == 3 || lst->read_meth == 4)
	{
		if (lst->sfd == 2)
			dup2(fd, lst->sfd);
		else
		{
			dup2(fd, 1);
			dup2(fd, 2);
		}
		close(fd);
	}
	else if (lst->read_meth == -2)
	{
		dup2(fd, 0);
		close(fd);
	}
	else if (lst->read_meth == -3)
		heredoc_broker(fds, lst);
}

int		redirect_to_fd(t_info *lst)
{
	if (lst->read_meth == -777)
		return (0);
	if (!lst->file)
	{
		if (lst->read_meth == -4)
		{
			if (lst->dfd && fcntl(lst->dfd, F_GETFD) == -1)
			{
				display_error(lst->dfd);
				return (0);
			}
			close((lst->sfd != -2) ? lst->sfd : 0);
		}
		else if (lst->dfd && lst->read_meth != -4)
		{
			if (!aggregation_fd(lst, true))
				return (0);
		}
		if (lst->read_meth == 5)
			if (!aggregation_fd(lst, false))
				return (0);
	}
	return (1);
}

int		deathly_hallows(t_info *lst)
{
	int		fd;

	while (lst)
	{
		if (!redirect_to_fd(lst))
			return (0);
		else if (lst->file != NULL && ft_strcmp(lst->file, "-1") != 0)
		{
			if ((fd = open_file(lst)) == -1)
			{
				return (0);
			}
			redirect_to_file(lst, fd);
		}
		lst = lst->next;
	}
	return (1);
}
