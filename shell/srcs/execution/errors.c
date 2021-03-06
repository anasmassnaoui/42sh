/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:18:23 by aariss            #+#    #+#             */
/*   Updated: 2019/08/10 16:35:32 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*error_assembly(int fd)
{
	char	*itoa;
	char	*tmp;

	itoa = ft_itoa(fd);
	tmp = itoa;
	itoa = ft_strjoin("42sh: ", itoa);
	ft_strdel(&tmp);
	tmp = itoa;
	itoa = ft_strjoin(itoa, ": bad file descriptor");
	ft_strdel(&tmp);
	return (itoa);
}

int		error_cases(char **arr)
{
	int	counter;

	counter = 0;
	while (arr[counter])
		counter++;
	if (counter > 3)
	{
		env_gerror(0);
		return (1);
	}
	counter = -1;
	while (arr[1][++counter])
	{
		if (!ft_isalpha(arr[1][counter]))
		{
			env_gerror(1);
			return (1);
		}
	}
	return (0);
}

void	path_gestion_error(char *path)
{
	char *msgerror;

	msgerror = ft_strjoin("command not found: ", path);
	ft_putendl_fd(msgerror, 2);
	ft_strdel(&msgerror);
	ft_strdel(&path);
}
