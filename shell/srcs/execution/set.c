/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:50:19 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 13:48:47 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		reset_hash(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)ft_memalloc(sizeof(char) * ft_strlen(s));
	while (s[i] && s[i] != '=')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	if (!ft_strcmp(tmp, "PATH"))
		to_reset_hash(1);
	ft_strdel((void *)&tmp);
	return (1);
}

void	newinenv(t_env **head_ref, char *s)
{
	t_env	*new_node;
	int		len;

	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	else
	{
		len = len_of_var(s);
		new_node->var = ft_strsub(s, 0, len);
		new_node->env = 0;
		new_node->value = ft_strdup(s + len);
	}
	new_node->next = NULL;
	if (!*head_ref)
		*head_ref = new_node;
	else
		add_node_1(*head_ref, new_node);
}

void	add_node1(t_env **head_ref, char *s)
{
	t_env	*current;
	int		is_new_var;
	char	**tabs;
	char	*tmp;

	tabs = splite_env(s);
	current = *head_ref;
	is_new_var = 1;
	while (current)
	{
		tmp = NULL;
		if (ft_strcmp((tmp = ft_strjoin(tabs[0], "=")), current->var) == 0
				&& reset_hash(s))
		{
			ft_strdel((void *)&current->value);
			current->value = ft_strdup(tabs[1]);
			is_new_var = 0;
		}
		ft_strdel((void *)&tmp);
		current = current->next;
	}
	(is_new_var) ? newinenv(head_ref, s) : 0;
	ft_free2d(tabs);
}

int		check_set(char *cmd)
{
	int i;

	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		if (i > 0 && !ft_isalpha(cmd[i])
			&& !ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (0);
}
