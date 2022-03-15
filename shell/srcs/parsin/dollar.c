/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:42:23 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 16:06:37 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*dollar_get_simple(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strdup(env->var);
		if (ft_strcmp(name, env->var) == 0)
		{
			*ptr = ft_strdup(str);
			ft_strdel(&str);
			return (env->value);
		}
		ft_strdel(&str);
		env = env->next;
	}
	return (NULL);
}

char	*dollar_get_quoted(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strdup(env->var);
		if (ft_strcmp(name, str) == 0)
		{
			*ptr = ft_strdup(str);
			ft_strdel(&str);
			return (env->value);
		}
		ft_strdel(&str);
		env = env->next;
	}
	return (NULL);
}

char	*dollar_handle_simple(char *toto, char *line, int *i, t_env *env)
{
	char	*str;
	char	*tmp;
	char	*kali;

	MAD_DECLARE(char*, ptr, NULL);
	kali = ft_strfchr_alpha(line + *i + 1);
	str = dollar_get_simple(kali, env, &ptr);
	ft_strdel(&kali);
	if (str)
	{
		tmp = toto;
		toto = ft_strjoin(toto, str);
		ft_strdel(&tmp);
		(*i) = (*i) + ft_strlen(ptr);
	}
	else
		skip_alpha(line, i);
	if (ptr)
		ft_strdel(&ptr);
	if (!ft_strlen(toto))
	{
		ft_strdel(&toto);
		return (NULL);
	}
	return (toto);
}

char	*dollar_in_quote(char *line, char *toto, int *i, t_quote sp)
{
	char	*str;
	char	*ptr;
	char	*kali;

	ptr = NULL;
	kali = ft_strfchr_alpha(line + *i + 1);
	str = dollar_get_quoted(kali, sp.env, &ptr);
	if (str)
	{
		toto = ft_strjoin_f(toto, str, 1);
		(*i) = (*i) + ft_strlen(ptr);
	}
	else
		skip_alpha(line, &(*i));
	ft_strdel(&kali);
	ft_strdel(&ptr);
	return (toto);
}

char	*dollar_handle_quoted(char *toto, char *line, int *i, t_quote sp)
{
	char *exit_status;

	exit_status = ft_itoa(get_set_holder(false, NULL)->last_status);
	ft_putendl("ddd");
	if (sp.keeper == 39)
		toto = ft_joinchar(toto, '$');
	else if (sp.keeper == '"')
	{
		if (line[*i + 1] == ' ' || line[*i + 1] == sp.keeper)
			return (ft_joinchar(toto, '$'));
		else if (line[(*i) + 1] == '?')
		{
			toto = ft_strjoin_f(toto, exit_status, 1);
			(*i) += 1;
		}
		else if (line[*i + 1] == '{')
			toto = dollar_curly(line, toto, i, sp.env);
		else
			toto = dollar_in_quote(line, toto, i, sp);
	}
	ft_strdel(&exit_status);
	return (toto);
}
