/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:43:29 by aariss            #+#    #+#             */
/*   Updated: 2020/01/31 20:03:27 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	assigner(char *command, t__mc **element)
{
	if (ft_strchr(command, AND))
		(*element)->def = 1;
	else if (ft_strchr(command, OR))
		(*element)->def = 2;
	else if (ft_strchr(command, BACKGROUND_AND))
		(*element)->def = 3;
	else if (!ft_strcmp(command, ";") && !ft_strchr(command, -19))
		(*element)->def = 4;
	else
		(*element)->def = 0;
	(*element)->cmd = ft_strsplit(command, -4);
}

t__mc	*mc_lst(char **mc)
{
	t__mc	*lst;
	t__mc	*head;
	int		i;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	i = 0;
	while (mc[i])
	{
		assigner(mc[i], &lst);
		i++;
		if (i == 1)
			head = lst;
		if (!mc[i])
			break ;
		if (!(lst->next = (t__mc*)malloc(sizeof(t__mc))))
			return (NULL);
		lst = lst->next;
	}
	lst->next = NULL;
	return (head);
}

int		count_delim(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ';')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

t__mc	*make_one_mc(char *line)
{
	t__mc	*lst;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	if (!(lst->cmd = (char**)malloc(sizeof(char*) * 2)))
		return (0);
	lst->cmd[0] = ft_strdup(line);
	lst->cmd[1] = NULL;
	lst->next = NULL;
	return (lst);
}

t__mc	*mc_maker(t_holder *h)
{
	char		**slice;
	char		*parsed;
	t__mc		*lst;

	if (count_delim(h->line))
		return (NULL);
	alias_parse(h);
	parsed = parsin(h);
	if (ft_strlen(parsed) == 0)
	{
		ft_strdel(&parsed);
		return (make_one_mc(" "));
	}
	else
	{
		slice = ft_strsplit(parsed, -3);
		ft_strdel(&parsed);
		lst = mc_lst(slice);
		ft_free2d(slice);
	}
	return (lst);
}
