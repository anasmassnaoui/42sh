/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:35:59 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 22:36:00 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*freed_strlchr_mod(char *str, char c)
{
	char *tmp;

	tmp = str;
	str = ft_strlchr_mod(str, c);
	ft_strdel(&tmp);
	return (str);
}

char	*merge_path(char *current, char *path)
{
	if (ft_strlen(current) != 1)
		kill_one(current, '/');
	current = ft_strjoin_f(current, "/", 1);
	current = ft_strjoin_f(current, path, 1);
	return (current);
}

char	*fill_current(char *current, char *tableau)
{
	if (ft_strcmp(tableau, "..") == 0)
		current = freed_strlchr_mod(current, '/');
	else if (ft_strcmp(tableau, ".") && ft_strcmp(tableau, ".."))
		current = merge_path(current, tableau);
	return (current);
}

char	*assemble_path(char *current, char *path)
{
	char	**tableau;
	char	**head;

	tableau = NULL;
	if (ft_strncmp(path, "/", 1) == 0)
	{
		ft_strdel(&current);
		return (ft_strdup(kill_one(path, '/')));
	}
	else if (ft_strlen(path) > 1 && ft_strchr(path, '/'))
		tableau = ft_strsplit(path, '/');
	else if (ft_strcmp(path, "..") == 0)
		return (freed_strlchr_mod(current, '/'));
	else if (ft_strcmp(path, ".") == 0)
		return (current);
	else
		return (merge_path(current, path));
	head = tableau;
	while (*tableau)
	{
		current = fill_current(current, *tableau);
		tableau += 1;
	}
	ft_free2d(head);
	return (current);
}

char	*current_dir_manager(t_holder *h)
{
	char	*current_dir_path;

	current_dir_path = get_var("PWD", &h->head_ref);
	if (!current_dir_path)
		current_dir_path = ft_strdup("");
	return (current_dir_path);
}
