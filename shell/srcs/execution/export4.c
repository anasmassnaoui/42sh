/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:11:53 by myamani           #+#    #+#             */
/*   Updated: 2020/02/13 18:11:55 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		export_option(char **args, int *option, int *index)
{
	int i;

	*option = 1;
	i = 0;
	while (args[++i])
	{
		if (args[i][0] != '-')
		{
			*option = 0;
			*index = i;
			break ;
		}
		if (ft_strcmp(args[i], "-p"))
		{
			ft_dprintf(2, "export: %s: invalid option\n", args[i]);
			return (0);
		}
		else
			*option = 2;
	}
	return (1);
}

void	ft_print_export(t_env *head_ref)
{
	while (head_ref)
	{
		if (head_ref->env)
		{
			ft_putstr("export ");
			(head_ref->value) ? ft_putstr(head_ref->var) :
			ft_putendl(head_ref->var);
			(head_ref->value) ? ft_putstr("=") : 0;
			(head_ref->value) ? ft_putvalue(head_ref->value) : 0;
			ft_putendl("");
		}
		head_ref = head_ref->next;
	}
}

t_env	*ft_find_decalarion(t_env *head_ref, char *key)
{
	while (head_ref)
	{
		if (!ft_strcmp(head_ref->var, key))
			return (head_ref);
		head_ref = head_ref->next;
	}
	return (NULL);
}

void	ft_export_declare2(t_varss *v, t_env **head_ref, t_bool global)
{
	v->new = (!v->new) ? (t_env *)malloc(sizeof(t_env)) : 0;
	v->new->env = global;
	v->new->var = ft_strdup(v->key_val_split[0]);
	v->new->value = (v->key_val_split[1])
	? ignore_quote(v->key_val_split[1], 1) : NULL;
	v->new->value_copy = NULL;
	v->new->next = *head_ref;
	*head_ref = v->new;
}
