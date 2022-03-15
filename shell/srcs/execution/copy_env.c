/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:44:02 by myamani           #+#    #+#             */
/*   Updated: 2020/01/21 21:44:06 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*copy_env(t_env *env)
{
	t_env *copy;
	t_env *head;

	copy = (t_env *)malloc(sizeof(t_env));
	head = copy;
	while (env)
	{
		if (env->var)
		{
			copy->var = ft_strdup(env->var);
			copy->env = (env->env == 0 || env->env == 1) ? env->env : 0;
			if (env->value)
				copy->value = ft_strdup(env->value);
			if (env->next == NULL)
				break ;
			copy->next = (t_env *)malloc(sizeof(t_env));
			copy = copy->next;
		}
		env = env->next;
	}
	copy->next = NULL;
	return (head);
}
