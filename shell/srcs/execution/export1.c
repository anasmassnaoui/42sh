/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:21:58 by myamani           #+#    #+#             */
/*   Updated: 2020/02/17 14:33:26 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		temporaire_variable(int i)
{
	static int tmp;

	if (i == 0)
		tmp = 0;
	else if (i == 1)
		tmp = 1;
	return (tmp);
}

int		check_in_not_valid(char c, int j, int q)
{
	return (((c == '\'' && q == 2) || (c == '"' && q == 1) ||
		(j > 0 && ft_isalnum(c) == 0 && c != '_'
		&& c != '$' && c != '{' && c != '}' && c != '\''
		&& c != '"')));
}

int		not_valid_identifier(char *token, int j, int q)
{
	while (token[j] && (token[j] == '\'' || token[j] == '"'))
		j++;
	if (!ft_isalpha(token[j]) && token[j] != '_' && token[j] != '$')
	{
		ft_dprintf(2, "42sh: export: `%s': not a valid identifier\n", token);
		return (1);
	}
	j = 0;
	while (token[j] && (token[j] != '=' || q != 0 || j == 0))
	{
		if (check_in_not_valid(token[j], j, q) || q)
		{
			ft_dprintf(2, "42sh: export: `%s': not a valid identifier\n",
			token);
			get_set_holder(false, NULL)->last_status = 1;
			return (1);
		}
		else if (token[j] == '\'')
			q = (q == 1) ? 0 : 1;
		else if (token[j] == '"')
			q = (q == 2) ? 0 : 2;
		j++;
	}
	return (0);
}

int		splite_env1(char const *s, t_varss *v)
{
	if (s[v->i] == '=')
	{
		v->argv[0][v->i + 1] = '\0';
		v->argv[1] = ft_strsub(s, v->i + 1, ft_strlen(s) - v->i);
		return (1);
	}
	else
		v->argv[1] = NULL;
	if (s[v->i] == '\'' || s[v->i] == '"')
	{
		v->c = s[v->i++];
		while (s[v->i] && s[v->i] != 'c')
			v->argv[0][v->x++] = s[v->i++];
		v->argv[0][v->x++] = s[v->i++];
	}
	v->argv[0][v->x++] = s[v->i++];
	return (0);
}

char	**splite_env(char const *s)
{
	t_varss v;

	if (!s)
		return (NULL);
	if (!(v.argv = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	v.i = 0;
	v.x = 0;
	v.argv[0] = (char *)ft_memalloc(sizeof(char) * ft_strlen(s));
	while (s[v.i])
	{
		if (splite_env1(s, &v))
			break ;
	}
	v.argv[2] = NULL;
	return (v.argv);
}
