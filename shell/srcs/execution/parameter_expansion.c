/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:28:45 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 16:01:16 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exit_status_expansion(int i)
{
	static int exit_status;

	if (i == 1)
		exit_status = 1;
	else if (i == 0)
		exit_status = 0;
	return (exit_status);
}

void	parameter_expansion1(t_expansion *exp, t_env *env)
{
	if (exp->value_len)
	{
		if (exp->symbol && !exit_status_expansion(-1)
		&& exit_status_expansion(1)
		&& (get_set_holder(false, NULL)->last_status = 1))
			ft_dprintf(2, "42sh: %s: bad substitution 4\n", exp->token);
		exp->final_string = ft_itoa(ft_strlen(exp->value));
	}
	else if (exp->symbol)
		do_symbol(exp, env);
	else if (exp->value)
		exp->final_string = ft_strdup(exp->value);
}

char	*parameter_expansion(char *token, t_env *env)
{
	char		*value;
	t_expansion	exp;

	value = NULL;
	exp.token = token;
	exp.value = NULL;
	exp.word = NULL;
	exit_status_expansion(0);
	exp.final_string = NULL;
	(get_set_holder(0, 0)->test) ? ft_strdel(&exp.parameter) : 0;
	(get_set_holder(0, 0)->test) ? ft_strdel(&token) : 0;
	if (get_set_holder(0, 0)->test)
		return (NULL);
	get__expansions(&exp, env);
	if (!ft_strcmp(exp.parameter, "$") && !exit_status_expansion(-1))
		exp.value = ft_itoa(getpid());
	else if (!ft_strcmp(exp.parameter, "?"))
		exp.value = ft_itoa(get_set_holder(false, NULL)->last_status);
	if (!parameter_errors(&exp))
		parameter_expansion1(&exp, env);
	if (exit_status_expansion(-1))
		get_set_holder(false, NULL)->last_status = exit_status_expansion(-1);
	free_exp(&exp);
	return (exp.final_string);
}
