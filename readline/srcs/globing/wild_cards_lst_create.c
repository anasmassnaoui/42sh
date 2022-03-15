/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards_lst_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:37:05 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 15:41:30 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

t_content	*create_content(char *name, int type)
{
	t_content	*new;

	if (!(new = (t_content*)malloc(sizeof(t_content))))
		return (NULL);
	new->name = ft_strdup(name);
	new->type = type;
	new->next = NULL;
	return (new);
}

void		lst_compose(t_dirent *rdir,
	t_content **lst, t_content **head, t_map map)
{
	if (match_glob(rdir->d_name, map.hint) == 1)
	{
		if (!(*head))
		{
			*lst = create_content(rdir->d_name, (int)rdir->d_type);
			*head = *lst;
		}
		else
		{
			(*lst)->next = create_content(rdir->d_name, (int)rdir->d_type);
			*lst = (*lst)->next;
		}
	}
}

t_content	*fill_list(DIR *directory, t_map wild_map)
{
	t_dirent	*rdir;
	t_content	*lst;
	t_content	*head;

	head = NULL;
	while ((rdir = readdir(directory)) != NULL)
	{
		if (rdir->d_name[0] != '.')
			lst_compose(rdir, &lst, &head, wild_map);
	}
	return (head);
}
