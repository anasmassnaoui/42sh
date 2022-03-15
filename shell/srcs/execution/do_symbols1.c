/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_symbols1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:22:52 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 14:09:06 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_env_in(char *key, t_env *env)
{
	char *str;

	str = NULL;
	if (key)
		str = ft_strjoin(key, "=");
	if (str && env)
		while (env)
		{
			if (!ft_strcmp(str, env->var))
			{
				ft_strdel((void *)&str);
				return (1);
			}
			env = env->next;
		}
	if (str)
		ft_strdel((void *)&str);
	return (0);
}

void	minus(t_expansion *exp)
{
	if (exp->symbol[0] == '-')
	{
		if (exp->value)
		{
			if (ft_strlen(exp->value) == 0)
				exp->final_string = NULL;
			else
				exp->final_string = ft_strdup(exp->value);
		}
		else if (exp->word)
			exp->final_string = ft_strdup(exp->word);
	}
	else if (exp->symbol[0] == ':')
	{
		if (exp->value && ft_strlen(exp->value))
			exp->final_string = ft_strdup(exp->value);
		else if (exp->word)
			exp->final_string = ft_strdup(exp->word);
	}
}

void	egale(t_expansion *exp, t_env *env, char *kv)
{
	kv = ft_strjoin(exp->parameter, "=");
	kv = ft_strjoin_f(kv, (exp->word) ? exp->word : "", 1);
	if (!ft_strcmp(exp->symbol, ":="))
	{
		if (exp->value && ft_strlen(exp->value))
			exp->final_string = ft_strdup(exp->value);
		else if (exp->parameter)
		{
			ft_export_declare(&get_set_holder(0, 0)->head_ref, kv, 0, false);
			(exp->word) ? exp->final_string = ft_strdup(exp->word) : 0;
		}
	}
	else if (!ft_strcmp(exp->symbol, "="))
	{
		if (exp->value && ft_strlen(exp->value))
			exp->final_string = ft_strdup(exp->value);
		else if (check_env_in(exp->parameter, env))
			exp->final_string = NULL;
		else if (check_env_in(exp->parameter, env) == 0)
		{
			ft_export_declare(&get_set_holder(0, 0)->head_ref, kv, 0, false);
			(exp->word) ? exp->final_string = ft_strdup(exp->word) : 0;
		}
	}
	free(kv);
}
