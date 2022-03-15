/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_envirement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:02 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/06 21:50:25 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*get_var_rl(char *deli, t_env *head_ref)
{
	t_env *current;

	current = head_ref;
	if (current)
		while (current)
		{
			if (current->var)
				if (ft_strcmp(deli, current->var) == 0)
				{
					if (current->value)
						return (ft_strdup(current->value));
					return (NULL);
				}
			current = current->next;
		}
	return (NULL);
}

void	get_en_rl(t_line *line, t_env *env)
{
	(*line).path = get_var_rl("PATH", env);
	(*line).home = get_var_rl("HOME", env);
}
