/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:16:04 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 15:32:56 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_match(char *str, char *in, int i, int j)
{
	while (str[i] == in[j])
	{
		i++;
		j++;
	}
	if (str[i] == 0)
		return (j);
	return (0);
}

int		check_double_hashtag(t_expansion *exp, int *i, int *j)
{
	return (exp->word[(*i)] == '*' && exp->word[(*i) + 1] == exp->value[(*j)]
	&& (exp->word[(*i) + 1] || !ft_strcmp(exp->symbol, "##")));
}

int		double_hashtag1(t_expansion *exp, int *i, int *j)
{
	int start;

	start = 0;
	while (exp->word[(*i)] == '*' && exp->word[(*i) + 1] == '*')
		(*i)++;
	if (check_double_hashtag(exp, i, j))
	{
		if ((start = is_match(exp->word, exp->value, (*i) + 1, (*j))))
		{
			if (*(exp->value + start - 1))
			{
				(exp->final_string) ? ft_strdel((void *)&exp->final_string) : 0;
				exp->final_string = ft_strdup(exp->value + start);
				if (!ft_strcmp(exp->symbol, "#"))
					return (1);
			}
			else
				ft_strdel((void *)&exp->final_string);
			(*i)++;
		}
	}
	if (exp->word && exp->word[(*i)] == 0)
		(*i) = 0;
	return (0);
}

void	double_hashtag(t_expansion *exp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!exp || (exp && !exp->value))
		exp->final_string = NULL;
	else if (exp->word && !ft_strchr(exp->word, '*'))
		hashtag(exp);
	else if (exp->word)
	{
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
		while (exp->value[j] && exp->word[i] &&
		(exp->value[j] == exp->word[i] || exp->word[i] == '*'))
		{
			if (exp->value[j] != exp->word[i] && exp->word[i] != '*')
				break ;
			if (exp->word[i] != '*')
				i++;
			j++;
			if (double_hashtag1(exp, &i, &j))
				break ;
		}
	}
}

void	hashtag(t_expansion *exp)
{
	int i;
	int is_match;

	is_match = 0;
	i = 0;
	if (exp->value && exp->word)
		while (exp->value[i] == exp->word[i])
		{
			i++;
			if (exp->word[i] == '\0' && (is_match = 1))
				exp->final_string = ft_strdup(exp->value + i);
		}
	if (!is_match)
		exp->final_string = (exp->value) ? ft_strdup(exp->value) : NULL;
}
