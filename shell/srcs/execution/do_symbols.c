/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_symbols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:28:59 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 15:55:12 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	colon_question(t_expansion *exp)
{
	if (exp->value && ft_strlen(exp->value))
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
	else if (!ft_strcmp(exp->parameter, "$"))
	{
		ft_dprintf(2, "42sh: %s: parameter null or not set\n",
		exp->parameter);
		ft_strdel((void *)&exp->final_string);
		exit_status_expansion(1);
	}
	else if (!exit_status_expansion(-1) && exit_status_expansion(1))
		ft_dprintf(2, "42sh: %s: parameter null or not set\n", exp->parameter);
}

void	question(t_expansion *exp)
{
	if (exp->value)
	{
		if (ft_strlen(exp->value))
			exp->final_string = ft_strdup(exp->value);
	}
	else if (!ft_strcmp(exp->parameter, "?"))
	{
		ft_dprintf(2, "42sh: %s: parameter null or not set\n", exp->parameter);
		ft_strdel((void *)&exp->final_string);
		exit_status_expansion(1);
	}
	else if (!exit_status_expansion(-1) && exit_status_expansion(1))
		ft_printf("42sh: %s: parameter null or not set\n", exp->parameter);
}

void	plus(t_expansion *exp)
{
	if (exp->value && ft_strlen(exp->value) && !ft_strcmp(exp->symbol, ":+"))
	{
		ft_strdel((void *)&exp->final_string);
		exp->final_string = (exp->word) ? ft_strdup(exp->word) : NULL;
	}
	else if (exp->value && !ft_strcmp(exp->symbol, "+"))
	{
		ft_strdel((void *)&exp->final_string);
		exp->final_string = (exp->word) ? ft_strdup(exp->word) : NULL;
	}
}

void	do_symbol(t_expansion *exp, t_env *env)
{
	if (!ft_strcmp(exp->symbol, ":"))
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
	else if (ft_strchr(exp->symbol, '-'))
		minus(exp);
	else if (ft_strchr(exp->symbol, '='))
		egale(exp, env, NULL);
	else if (!ft_strcmp(exp->symbol, ":?"))
		colon_question(exp);
	else if (!ft_strcmp(exp->symbol, "?"))
		question(exp);
	else if (ft_strchr(exp->symbol, '+'))
		plus(exp);
	else if (exp->symbol[0] == '%')
		double_modulo(exp);
	else if (exp->symbol[0] == '#')
		double_hashtag(exp);
}

int		parameter_errors(t_expansion *exp)
{
	int			i;
	static int	r;
	int			error;

	error = 0;
	i = 0;
	if (ft_strchr(exp->parameter, '\'') || ft_strchr(exp->parameter, '"') ||
			ft_strchr(exp->parameter, ' ') || ft_strchr(exp->parameter, '\t') ||
			ft_strchr(exp->parameter, '\n'))
		error = 1;
	if (error && exit_status_expansion(1) && (r = !r))
		ft_dprintf(2, "42sh: ${%s}: bad substitution 2\n", exp->parameter);
	return (error);
}
