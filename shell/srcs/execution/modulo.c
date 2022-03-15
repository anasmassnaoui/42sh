/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:59:44 by myamani           #+#    #+#             */
/*   Updated: 2020/01/27 16:01:03 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_match_rev(char *str, char *in, int i, int j)
{
	while (str[i] == in[j])
	{
		i--;
		j--;
	}
	if (i == -1)
		return (j + 1);
	return (0);
}

void	modulo(t_expansion *exp)
{
	int len_value;
	int len_word;
	int is_match;

	len_value = ft_strlen(exp->value);
	len_word = ft_strlen(exp->word);
	is_match = 0;
	if (exp->word && exp->value)
		while (exp->value[len_value] == exp->word[len_word])
		{
			if (len_word == 0)
			{
				exp->final_string = ft_strdup(exp->value);
				exp->final_string[len_value] = '\0';
				is_match = 1;
			}
			len_value--;
			len_word--;
		}
	if (is_match == 0)
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
}

int		double_modulo2(t_expansion *exp, t_varss *v)
{
	int start;

	if ((start = is_match_rev(exp->word, exp->value, (v->i) - 1, (v->j)))
	|| (v->j) == -1)
	{
		if ((v->j) == -1)
			start = 0;
		if (start <= (int)ft_strlen(exp->value))
		{
			ft_strdel((void *)&exp->final_string);
			exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
			exp->final_string[start] = 0;
			if (!ft_strcmp(exp->symbol, "%"))
				return (1);
		}
		else
			ft_strdel((void *)&exp->final_string);
		(v->i)--;
	}
	return (0);
}

int		double_modulo1(t_expansion *exp, t_varss *v)
{
	while (exp->word[(v->i)] == '*' && exp->word[(v->i) - 1] == '*')
		(v->i)--;
	if (exp->word[(v->i)] == '*' && (v->i == 0 || exp->word[(v->i) - 1])
	&& exp->word[(v->i) - 1] == exp->value[(v->j)]
	&& (v->i > 0 || !ft_strcmp(exp->symbol, "%%")))
	{
		if (double_modulo2(exp, v))
			return (1);
		ft_strdel((void *)&exp->final_string);
	}
	if ((v->i) == 0)
		(v->i) = ft_strlen(exp->word) - 1;
	return (0);
}

void	double_modulo(t_expansion *exp)
{
	t_varss v;

	v.j = ft_strlen(exp->value) - 1;
	v.i = ft_strlen(exp->word) - 1;
	if (exp->word && !ft_strchr(exp->word, '*'))
		modulo(exp);
	else
	{
		ft_strdel(&exp->final_string);
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
		while (exp->value && exp->word && exp->value[v.j]
		&& (exp->value[v.j] == exp->word[v.i] || exp->word[v.i] == '*'))
		{
			if (exp->value[v.j] != exp->word[v.i] && exp->word[v.i] != '*')
				break ;
			if (exp->word[v.i] != '*')
				v.i--;
			v.j--;
			if (double_modulo1(exp, &v))
				break ;
		}
	}
}
