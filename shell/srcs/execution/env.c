/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:08:38 by amassnao          #+#    #+#             */
/*   Updated: 2020/02/17 13:33:24 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_val_copy(t_env *head_ref)
{
	while (head_ref)
	{
		if (head_ref->value_copy)
			free(head_ref->value_copy);
		head_ref->value_copy = (head_ref->value) ?
		ft_strdup(head_ref->value) : NULL;
		head_ref = head_ref->next;
	}
}

void	env_diff(t_env **head_ref, t_env *prev, t_env *head)
{
	if (!head)
		return ;
	if (head->next)
		env_diff(head_ref, head, head->next);
	if (head->value_copy)
	{
		if (head->env == 3)
			head->env = 0;
		free(head->value);
		head->value = head->value_copy;
		head->value_copy = NULL;
	}
	if (head->env == 3)
	{
		if (!prev)
			*head_ref = head->next;
		else
			prev->next = head->next;
		free(head->var);
		free(head->value);
		free(head->value_copy);
		free(head);
	}
}

void	extract_env(t_holder *h)
{
	int		index;
	t_list	*new;
	int		i;

	if (!h->lst->cmd || !h->lst->cmd[0] || !check_set(h->lst->cmd[0]))
		return ;
	i = 0;
	while (h->lst->cmd[i])
	{
		if (check_set(h->lst->cmd[i]))
		{
			new = (t_list *)malloc(sizeof(t_list));
			new->content = h->lst->cmd[i];
			new->next = h->tmp_env;
			h->tmp_env = new;
		}
		else
			break ;
		i++;
	}
	index = i;
	i = 0;
	while (h->lst->cmd[i])
		h->lst->cmd[i++] = h->lst->cmd[index++];
}

void	del_env(t_env **head_ref, t_env *prev, t_env *node, char *key)
{
	if (!node)
		return ;
	if (node->next)
		del_env(head_ref, node, node->next, key);
	if (!ft_strcmp(node->var, key))
	{
		if (prev)
			prev->next = node->next;
		else
			*head_ref = node->next;
		free(node->var);
		free(node->value);
		free(node->value_copy);
		free(node);
		return ;
	}
}
