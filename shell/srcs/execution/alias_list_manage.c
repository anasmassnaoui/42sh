/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_list_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:39:36 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:47:36 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	del_one_alias(t_alias **one)
{
	ft_strdel(&(*one)->alias);
	ft_strdel(&(*one)->original);
	free(*one);
	*one = NULL;
}

t_alias	*tail(t_alias *alias)
{
	t_alias *tail;

	tail = alias;
	if (tail)
		while (tail->next != NULL)
			tail = tail->next;
	return (tail);
}

void	unalias(t_alias **alias, char *name)
{
	t_alias *head;
	t_alias *previous;
	t_alias *tmp;

	head = *alias;
	if (ft_strcmp(head->alias, name) == 0)
	{
		tmp = head;
		head = head->next;
		*alias = head;
	}
	else
	{
		previous = head;
		while (head && !(ft_strcmp(head->alias, name) == 0))
		{
			previous = head;
			head = head->next;
		}
		tmp = head;
		previous->next = head->next;
	}
	del_one_alias(&tmp);
}

int		edit_alias(t_alias **alias, char *name)
{
	char	*ptr;
	char	*str;
	t_alias *head;

	head = *alias;
	ptr = ft_strchr(name, '=') + 1;
	str = ft_strfchr(name, '=');
	while (head)
	{
		if (ft_strcmp(head->alias, str) == 0)
		{
			ft_strdel(&head->original);
			if (count_accurance(ptr, '"') == 0 && count_accurance(ptr, 39) == 0)
				head->original = ft_strdup(ptr);
			else
				head->original = ignore_quote(ptr, 1);
			ft_strdel(&str);
			return (1);
		}
		head = head->next;
	}
	ft_strdel(&str);
	return (0);
}

t_alias	*set_alias(t_alias *alias, char *name, t_alias *end)
{
	t_alias *head;
	int		edited;
	char	**tableau;

	head = alias;
	tableau = ft_shell_strsplit(name, '=', "YES");
	edited = edit_alias(&alias, name);
	if (edited == 1 && head)
	{
		ft_free2d(tableau);
		return (head);
	}
	else if (edited == 0 && head)
	{
		end->next = create_alias_element(tableau[0], tableau[1]);
		ft_free2d(tableau);
		return (head);
	}
	else
		head = create_alias_element(tableau[0], tableau[1]);
	ft_free2d(tableau);
	return (head);
}
