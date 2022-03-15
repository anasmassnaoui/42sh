/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 10:47:07 by aariss            #+#    #+#             */
/*   Updated: 2020/01/17 18:10:33 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			fill_line(char **ptr, char **line, char c)
{
	char			*ptrchr;
	size_t			i;
	size_t			pos;
	char			*d;

	i = 0;
	if ((ptrchr = ft_strchr(*ptr, c)))
	{
		i = ft_strlen(ptrchr);
		pos = ft_strlen(*ptr) - i;
		*line = ft_strsub(*ptr, 0, pos);
		d = ft_strsub(*ptr, pos + 1, ft_strlen(*ptr) - pos);
		ft_strdel(&(*ptr));
		*ptr = d;
	}
	else
	{
		*line = ft_strdup(*ptr);
		ft_strdel(&(*ptr));
		if (*line[0] == '\0')
			return (0);
	}
	return (1);
}

int					get_next_line(const int fd, char **line, char c)
{
	int				red;
	static	char	*ptr[100];
	char			*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!ptr[fd])
		ptr[fd] = ft_strnew(1);
	if (!(ft_strchr(ptr[fd], '\n')))
	{
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (-1);
		while ((red = read(fd, buf, BUFF_SIZE)))
		{
			if (red < 0)
				return (-1);
			buf[red] = '\0';
			ptr[fd] = ft_strjoin_f(ptr[fd], buf, 1);
			if (ft_strchr(buf, c))
				break ;
		}
		ft_strdel(&buf);
	}
	return (fill_line(&ptr[fd], line, c));
}
