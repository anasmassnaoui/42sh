/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:04:41 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 15:55:19 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_bad_substitution(int **i, t_expansion *exp)
{
	return (**i > 2 && exp->token[(**i)] == '$'
			&& exit_status_expansion(1));
}

void	check_symbols1(t_expansion *exp, int **i)
{
	if (exp->token[(**i)] == '#')
	{
		exp->symbol[0] = exp->token[(**i)++];
		if (exp->token[(**i)] == '#')
		{
			exp->symbol[1] = exp->token[(**i)++];
			exp->symbol[2] = '\0';
		}
	}
	else if (exp->token[(**i)] == '%')
	{
		exp->symbol[0] = exp->token[(**i)++];
		if (exp->token[(**i)] == '%')
		{
			exp->symbol[1] = exp->token[(**i)++];
			exp->symbol[2] = '\0';
		}
	}
	else if (check_bad_substitution(i, exp))
		ft_dprintf(2, "42sh: %s: bad substitution 3\n", exp->token);
}

void	check_symbols(t_expansion *exp, int *i)
{
	if (!(exp->symbol = (char *)ft_memalloc(sizeof(char) * 3)))
		return ;
	exp->symbol[1] = '\0';
	if (exp->token[(*i)] == ':')
	{
		exp->symbol[0] = exp->token[(*i)++];
		if (exp->token[(*i)] == '+' || exp->token[(*i)] == '-'
				|| exp->token[(*i)] == '=' || exp->token[(*i)] == '?')
		{
			exp->symbol[1] = exp->token[(*i)++];
			exp->symbol[2] = '\0';
		}
	}
	else if (exp->token[(*i)] == '+' || exp->token[(*i)] == '-'
			|| exp->token[(*i)] == '=' || exp->token[(*i)] == '?')
	{
		exp->symbol[0] = exp->token[(*i)++];
		exp->symbol[1] = '\0';
	}
	else
		check_symbols1(exp, &i);
}

void	free_exp(t_expansion *exp)
{
	ft_strdel((void *)&exp->parameter);
	ft_strdel((void *)&exp->symbol);
	ft_strdel((void *)&exp->token);
	ft_strdel((void *)&exp->value);
	ft_strdel((void *)&exp->word);
	(exit_status_expansion(-1)) ? ft_strdel((void *)&exp->final_string) : 0;
}

int		check_parameter_expansion(char *arg)
{
	int		i;
	char	c;

	i = 0;
	while (arg[i])
	{
		ft_putchar(arg[i]);
		if (arg[i] == '\'' || arg[i] == '"')
		{
			c = arg[i++];
			while (arg[i] != c)
				i++;
			i++;
		}
		if (arg[i] == '$' && arg[i + 1] == '{')
			return (1);
		i++;
	}
	return (0);
}
