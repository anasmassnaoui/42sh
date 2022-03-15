/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:24:47 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 15:55:01 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_exp_token_end(char *token, int i, int len)
{
	return (i < (len - 1) && (!check_operators(token[i])
	|| (token[i] == '$' && (i == 2
	&& (len <= 4 || check_operators(token[i + 1]))))
	|| (token[i] == '?' && i == 2 && (len <= 4
	|| check_operators(token[i + 1])))));
}

int		check_operators(char c)
{
	return (c == ':' || c == '+' || c == '-'
			|| c == '=' || c == '#' || c == '%'
			|| c == '$' || c == '?' || c == '}');
}

void	print_error(t_expansion *exp)
{
	ft_dprintf(2, "42sh: %s: bad substitution 1\n", exp->token);
	exit_status_expansion(1);
}

void	handle_word(t_expansion *exp, int i)
{
	(exp->word) ? ft_strdel((void *)&exp->word) : 0;
	exp->word = ft_strdup(exp->token + i - 1);
	exp->word[ft_strlen(exp->word) - 1] = '\0';
}

void	get_parameter(t_expansion *exp, int len, int i)
{
	exp->value_len = 0;
	if (exp->token[2] == '#')
		exp->value_len = 1;
	if (!(exp->parameter =
	(char *)ft_memalloc(sizeof(char) * (len - (2 + exp->value_len)))))
		return ;
	i = 2 + exp->value_len;
	while (check_exp_token_end(exp->token, i, len))
	{
		exp->parameter[i - (2 + exp->value_len)] = exp->token[i];
		i++;
	}
	exp->parameter[i - (2 + exp->value_len)] = '\0';
	if ((exp->token[i] == '$' || i == 2)
	&& exit_status_expansion(-1) && exit_status_expansion(1))
		print_error(exp);
	exp->symbol = NULL;
	if (i < (len - 1) && !exit_status_expansion(-1))
		check_symbols(exp, &i);
	if (exp->token[++i] && !exit_status_expansion(-1))
		handle_word(exp, i);
}
