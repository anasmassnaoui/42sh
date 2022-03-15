/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 15:34:30 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/07 16:45:35 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		len_listt(t_env *lst)
{
	int		i;
	t_env	*tmp_history;

	i = 0;
	tmp_history = lst;
	while (tmp_history != NULL)
	{
		tmp_history = tmp_history->next;
		i++;
	}
	return (i);
}

char	**get_envv(t_env *head_ref)
{
	t_env	*current;
	char	**tabb;
	int		i;

	current = head_ref;
	if (!(tabb = (char **)malloc(sizeof(char *) * (len_listt(head_ref) + 1))))
		return (NULL);
	i = 0;
	while (current)
	{
		if (current->value)
			tabb[i] = ft_strjoin(current->var, current->value);
		else
			tabb[i] = ft_strdup(current->var);
		current = current->next;
		i++;
	}
	tabb[i] = NULL;
	return (tabb);
}
