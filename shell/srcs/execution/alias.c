/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:17:13 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:17:14 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		link_alias_list(t_alias **list,
	t_alias **head, char **tmp, t_index index)
{
	if (index.i == 0)
	{
		(*list) = create_alias_element(tmp[0], tmp[index.v]);
		(*head) = (*list);
	}
	else
	{
		(*list)->next = create_alias_element(tmp[0], tmp[index.v]);
		(*list) = (*list)->next;
	}
	ft_free2d(tmp);
}

int			in_between(char **alias, t_alias **list, t_alias **head, int *i)
{
	char	**tmp;
	char	*vacuum;
	t_index	index;

	index.i = *i;
	vacuum = NULL;
	tmp = ft_shell_strsplit(alias[*i], '=', "YES");
	if (count_accurance(tmp[1], '"') != 0 || count_accurance(tmp[1], 39) != 0)
	{
		vacuum = tmp[1];
		tmp[1] = ignore_quote(tmp[1], 1);
		ft_strdel(&vacuum);
	}
	if (count_tab(tmp) == 2)
		index.v = 1;
	else if (count_tab(tmp) == 3)
		index.v = 2;
	else
	{
		ft_putendl_fd("Wrong Alias Format", 2);
		ft_free2d(tmp);
		return (0);
	}
	link_alias_list(list, head, tmp, index);
	return (1);
}

int			alias_handler(t_holder *h)
{
	t_alias *aliases;

	aliases = h->aliases;
	if (ft_strchr_quoted(h->lst->cmd[1], '='))
		h->aliases = set_alias(aliases, h->lst->cmd[1], tail(aliases));
	else
	{
		if (!print_one_alias(h, aliases))
		{
			ft_putstr_fd("42sh: alias: ", 2);
			ft_putstr_fd(h->lst->cmd[1], 2);
			ft_putendl_fd(": not found", 2);
			return (0);
		}
	}
	return (1);
}

int			alias(t_holder *h, int alias_len)
{
	t_alias *aliases;

	aliases = h->aliases;
	if (alias_len == 1)
		list_aliases(aliases);
	else if (alias_len == 2)
	{
		if (!alias_handler(h))
			return (0);
	}
	else
	{
		ft_putendl_fd("Wrong Alias Format", 2);
		return (0);
	}
	return (1);
}

int			alias_manager(t_holder *h)
{
	int		alias_len;
	t_alias	*aliases;

	aliases = h->aliases;
	alias_len = count_tab(h->lst->cmd);
	if (ft_strcmp(h->lst->cmd[0], "alias") == 0)
	{
		if (!alias(h, alias_len))
			return (0);
	}
	else if (ft_strcmp(h->lst->cmd[0], "unalias") == 0)
	{
		if (check_unalias(h->lst->cmd, &aliases))
		{
			unalias(&aliases, h->lst->cmd[1]);
			h->aliases = aliases;
		}
	}
	return (1);
}
