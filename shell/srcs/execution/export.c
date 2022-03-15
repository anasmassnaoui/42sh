/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:57:09 by myamani           #+#    #+#             */
/*   Updated: 2020/02/13 18:08:29 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_export_declare1(t_varss *v, t_env **head_ref,
		t_bool global, t_bool force)
{
	if (v->new)
	{
		if (!v->new->env || global == 1)
			v->new->env = global;
		(!global || global == 1) ? free(v->new->value_copy) : 0;
		(!global || global == 1) ? v->new->value_copy = NULL : 0;
		(v->key_val_split[1] || force) ? free(v->new->value) : 0;
		if (!force)
			v->new->value = (v->key_val_split[1])
			? ignore_quote(v->key_val_split[1], 1) : v->new->value;
		else
			v->new->value = (v->key_val_split[1])
			? ignore_quote(v->key_val_split[1], 1) : NULL;
	}
	else
		ft_export_declare2(v, head_ref, global);
}

void	ft_export_declare(t_env **head_ref,
		char *key_val, t_bool global, t_bool force)
{
	t_varss v;

	if (not_valid_identifier(key_val, 0, 0))
		return ;
	v.key_val_split = splite_env(key_val);
	if (!global && !ft_strcmp("PATH", v.key_val_split[0]))
		to_reset_hash(1);
	v.new = ft_find_decalarion(*head_ref, v.key_val_split[0]);
	ft_export_declare1(&v, head_ref, global, force);
	ft_free2d(v.key_val_split);
}

int		ft_export(char **token, t_holder *h)
{
	int		option;
	int		index;

	token = rip_quotes(token);
	if (!export_option(token, &option, &index))
		return (1);
	if (option == 1)
		ft_print_export(h->head_ref);
	else if (option == 2)
		print_export(&h->head_ref, token);
	else
		while (token[index])
			ft_export_declare(&h->head_ref, token[index++], 1, 0);
	return (0);
}

void	copy_variables(t_env *env, char **cmd, int i)
{
	int		j;
	char	*str;
	t_env	*tmp;

	j = 0;
	while (j < i)
	{
		tmp = env;
		str = ft_join("%s=", cmd[j]);
		while (tmp)
		{
			if (ft_strcmp(tmp->var, str))
				tmp->env = 1;
			tmp = tmp->next;
		}
		ft_strdel((void *)&str);
		j++;
	}
}

void	ft_set(t_holder *h)
{
	print_env(&h->head_ref);
}
