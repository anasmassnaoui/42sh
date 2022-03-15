/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:09:21 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 17:54:09 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int			check_flags(char *ptr)
{
	if (!ft_strcmp(ptr, "-e") || !ft_strcmp(ptr, "-re")
	|| (!ft_strcmp(ptr, "-r")))
		return (1);
	else
		return (0);
}

void		fc_no_flags(t_history *tmp, char **ptr,
char **str, char **tab_env)
{
	char	*tmp_2;

	if (!which_one(tmp, ptr[1]))
	{
		ft_putendl("42sh: fc: history specification out of range");
	}
	else
	{
		tmp_2 = *str;
		fc_e("vim", str, tab_env, search_in_hist(tmp, ptr[1], ft_atoi(ptr[1])));
		ft_strdel(&tmp_2);
	}
}

char		*add_join(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(ptr) + 2)))
		return (0);
	while (ptr[i])
	{
		str[i] = ptr[i];
		i++;
	}
	str[i++] = ' ';
	str[i] = '\0';
	return (str);
}

char		*join_path(char *ptr)
{
	char	*line;
	char	*line2;
	char	*path;
	char	*str;

	path = file_path();
	str = add_join(ptr);
	line2 = ft_strjoin("/usr/bin/", str);
	line = ft_strjoin(line2, path);
	ft_strdel(&str);
	ft_strdel(&line2);
	ft_strdel(&path);
	return (line);
}

char		*file_path(void)
{
	char	*home_login;
	char	*path;

	home_login = ft_strjoin("/Users/", getlogin());
	path = ft_strjoin(home_login, "/.file");
	ft_strdel(&home_login);
	return (path);
}
