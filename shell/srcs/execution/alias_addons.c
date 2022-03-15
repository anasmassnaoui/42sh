/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_addons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:46:46 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:46:50 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_alias		*create_alias_element(char *alias, char *original)
{
	t_alias *element;

	if (!alias || !original)
		return (NULL);
	if (!(element = (t_alias *)malloc(sizeof(t_alias))))
		return (NULL);
	element->alias = ft_strdup(alias);
	if (count_accurance(original, '"') == 0
		&& count_accurance(original, 39) == 0)
		element->original = ft_strdup(original);
	else
		element->original = ignore_quote(original, 1);
	element->next = NULL;
	return (element);
}

int			count_accurance(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int			check_unalias(char **cmd, t_alias **alias)
{
	t_alias *head;

	head = *alias;
	if (cmd[1])
	{
		while (head)
		{
			if (ft_strcmp(cmd[1], head->alias) == 0)
				return (1);
			head = head->next;
		}
	}
	return (0);
}

char		*ft_strchr_quoted(const char *str, int c)
{
	int keeper;

	keeper = 0;
	while (*str && *str != (char)c)
	{
		if (ft_isquote(*str))
		{
			keeper = *str;
			str += 1;
			while (*str && *str != keeper)
				str += 1;
		}
		str += 1;
	}
	if (*str == (char)c)
		return ((char*)str);
	return (NULL);
}
