/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:32:53 by myamani           #+#    #+#             */
/*   Updated: 2020/02/08 21:29:20 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_value(t_expansion *exp, t_env *env)
{
	char *str;
	char *value;

	value = NULL;
	str = exp->parameter;
	while (env)
	{
		if (env->value && !ft_strcmp(str, env->var))
			value = ft_strdup(env->value);
		env = env->next;
	}
	return (value);
}

void	parse_word(t_expansion *exp, int i, int x)
{
	if (exp->word && exp->word[0])
	{
		exp->val1 = (char **)malloc(sizeof(char *) * 3);
		exp->val1[0] = (char *)malloc(sizeof(char) * ft_strlen(exp->word) + 1);
		exp->val1[1] = NULL;
		exp->val1[2] = NULL;
		while (exp->word[i])
			exp->val1[0][x++] = exp->word[i++];
		exp->val1[0][x] = '\0';
	}
}

int		check_word(t_expansion *exp)
{
	int i;
	int c;

	i = 0;
	while (exp->word[i])
	{
		if (exp->word[i] == '\'' || exp->word[i] == '"')
		{
			c = exp->word[i];
			while (exp->word[i] != c)
				i++;
			i++;
		}
		if (exp->word[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	get__expansions2(t_expansion *exp)
{
	parse_word(exp, 0, 0);
	(exp->word) ? ft_strdel((void *)&exp->word) : 0;
	exp->word = (exp->val1[0]) ? ft_strdup(exp->val1[0]) : NULL;
	ft_free2d(exp->val1);
}

void	get__expansions(t_expansion *exp, t_env *env)
{
	get_parameter(exp, ft_strlen(exp->token), 0);
	exp->value = get_value(exp, env);
	if (exp->word && check_word(exp))
		get__expansions2(exp);
}
