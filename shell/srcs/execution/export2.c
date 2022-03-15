/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:26:11 by myamani           #+#    #+#             */
/*   Updated: 2020/02/15 12:57:58 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*add_values(char **tabl)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 2;
	if (tabl[1])
		str = ft_strdup(tabl[1]);
	while (tabl[i])
	{
		tmp = str;
		str = ft_join("%s=%s", str, tabl[i++]);
		ft_strdel((void *)&tmp);
	}
	tabl[i] = NULL;
	return (str);
}

void	add_env(char **tableau, t_env **env, char *token)
{
	t_env	*new_node;
	char	*tmp;

	tmp = NULL;
	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	new_node->var = ft_join("%f=", ignore_quote(tableau[0], 1));
	new_node->env = 1;
	new_node->value = (tableau[1] && ft_strlen(tableau[1]))
	? ignore_quote((tmp = add_values(tableau)), 1) : ft_strdup("");
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else if (tableau[1] && !not_valid_identifier(token, 0, 0))
		add_node_1(*env, new_node);
	else
	{
		ft_strdel(&new_node->value);
		ft_strdel(&new_node->var);
		free(new_node);
	}
	(tmp) ? ft_strdel((void *)&tmp) : 0;
}

void	export_variables1(t_env *current, t_env **head_ref, char **token, int i)
{
	char	**tmp;
	char	*tmp1;
	int		var_found;

	tmp = splite_env(token[i]);
	var_found = 0;
	while (current)
	{
		if (!ft_strcmp(current->var,
					(tmp1 = ft_join("%f=", ignore_quote(tmp[0], 1)))))
		{
			current->env = 1;
			(tmp[1] && current->value) ? ft_strdel((void *)&current->value) : 0;
			current->value = (ignore_quote(tmp[1], 1))
			? ft_strdup(ignore_quote(tmp[1], 1)) : ft_strdup("");
			var_found = 1;
		}
		(tmp1) ? ft_strdel((void *)&tmp1) : 0;
		current = current->next;
	}
	if (!var_found)
		add_env(tmp, head_ref, token[i]);
	ft_free2d(tmp);
}

void	export_variables(t_env **head_ref, char **token)
{
	int i;

	i = 1;
	while (token[i])
	{
		if (not_valid_identifier(token[i], 0, 0) == 0)
		{
			export_variables1(*head_ref, head_ref, token, i);
			i++;
		}
		else
		{
			get_set_holder(false, NULL)->last_status = 1;
			if (token[i])
				i++;
		}
	}
}

void	print_exp(t_env *env, int i)
{
	while (env)
	{
		if (env->env)
		{
			i = 0;
			while (env->var[i])
			{
				(env->var[i] == '\'' || env->var[i] == '"')
				? ft_putchar('\\') : 0;
				ft_putchar(env->var[i++]);
			}
			i = 0;
			while (env->value && env->value[i])
			{
				(env->value[i] == '\'' || env->value[i] == '"')
				? ft_putchar('\\') : 0;
				ft_putchar(env->value[i++]);
			}
			ft_putendl("");
		}
		env = env->next;
	}
}
