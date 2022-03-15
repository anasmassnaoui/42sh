/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:38:25 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 16:38:27 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

DIR			*open_this(char *directory)
{
	DIR		*dir;
	t_stat	buffer;

	if (lstat(directory, &buffer) != -1)
	{
		if (S_ISDIR(buffer.st_mode))
			if ((dir = opendir(directory)) != NULL)
				return (dir);
	}
	else
		return (NULL);
	return (NULL);
}

t_content	*get_files_list(t_map wild_map)
{
	DIR			*dir;
	t_content	*lst;

	if (!(dir = open_this(wild_map.directory)))
		return (NULL);
	lst = fill_list(dir, wild_map);
	closedir(dir);
	return (lst);
}
