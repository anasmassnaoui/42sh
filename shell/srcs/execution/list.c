/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:59:55 by aariss            #+#    #+#             */
/*   Updated: 2020/02/13 18:29:06 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		len_of_var(char *s)
{
	int	index;

	index = 1;
	while (*s && *s++ != '=')
		index++;
	return (index);
}

void	createlist(t_env **head, t_env **tail, char *s)
{
	t_env	*new_node;
	int		index;

	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	index = len_of_var(s);
	new_node->var = ft_strsub(s, 0, index - 1);
	new_node->value = ft_strdup(s + index);
	new_node->value_copy = NULL;
	new_node->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = new_node;
		(*tail) = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		(*tail) = (*tail)->next;
	}
}

char	**get_env(t_env **head_ref)
{
	t_env	*current;
	char	**tableau;
	int		i;
	int		len;

	len = len_of_list(*head_ref) + 1;
	current = *head_ref;
	if (!(tableau = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	i = 0;
	while (current)
	{
		if (current->env)
		{
			tableau[i] = ft_strjoin(current->var, "=");
			if (current->value)
				tableau[i] = ft_strjoin_f(tableau[i], current->value, 1);
			i++;
		}
		current = current->next;
	}
	tableau[i] = NULL;
	return (tableau);
}

void	del_node1(t_varss *v)
{
	ft_strdel(&v->current->var);
	if (v->current->value)
		ft_strdel(&v->current->value);
	free(v->current);
}

void	del_node(char *s, t_env **head_ref)
{
	if (not_valid_identifier(s, 0, 0))
		return ;
	if (!ft_strcmp(s, "PATH"))
		to_reset_hash(1);
	del_env(head_ref, NULL, *head_ref, s);
}
