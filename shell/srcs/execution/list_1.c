/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:31:34 by aariss            #+#    #+#             */
/*   Updated: 2020/02/13 18:26:04 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		len_of_list(t_env *current)
{
	int		counter;

	counter = 0;
	while (current)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}

void	print_env(t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
		ft_putstr(current->var);
		(current->value) ? ft_putstr("=") : ft_putendl("=");
		(current->value) ? ft_putendl(current->value) : 0;
		current = current->next;
	}
}

char	*get_var(char *deli, t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
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

void	swap(t_env **head_ref, char *lastcwd, char *cwd)
{
	t_env	*current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp("OLDPWD", current->var) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(lastcwd);
		}
		if (ft_strcmp("PWD", current->var) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(cwd);
		}
		current = current->next;
	}
}

t_env	*copy_of_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	if (env[0])
	{
		while (env[++i])
			createlist(&head, &tail, env[i]);
		tail = head;
		while (head)
		{
			head->env = 1;
			head = head->next;
		}
	}
	head = tail;
	return (head);
}
