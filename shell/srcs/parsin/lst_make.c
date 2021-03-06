/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:39:26 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 14:27:31 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sure_darlin(char **kratos, t_cmd **lst, t_info **head, t_index *l)
{
	t_index	def;

	if (l->v == 0)
	{
		def.i = 0;
		def.j = 0;
		(*lst)->red = create_info(kratos[l->i], NULL, &(*l), def);
		*head = (*lst)->red;
	}
	if (l->v == 777)
	{
		def.i = 777;
		def.j = 0;
		(*lst)->red = create_info(kratos[l->i], NULL, &(*l), def);
		*head = (*lst)->red;
	}
}

void	not_known_as_if(char **kratos, t_cmd **lst, int *t)
{
	t_index	l;
	t_info	*head;

	l.i = 0;
	l.j = 0;
	l.v = 0;
	if (!((*lst)->cmd = (char **)malloc(sizeof(char *) * count_arg(kratos))))
		return ;
	while (kratos[l.i])
	{
		if (ultimate_check(kratos[l.i]) == 1)
			add_file(&(*lst), &head, kratos, &l);
		else if (ultimate_check(kratos[l.i]) == 2)
			add_casual(&(*lst), &head, kratos, &l);
		else if (got_no_token(kratos[l.i]) || !ft_strchr(kratos[l.i], -5))
			(*lst)->cmd[l.j++] = ft_strdup(kratos[l.i]);
		l.i++;
	}
	sure_darlin(kratos, &(*lst), &head, &l);
	(*lst)->cmd[l.j] = NULL;
	(*lst)->red = head;
	(*t)++;
}

void	tilde_fix(char **cmd, t_env *env)
{
	int		i;
	char	*tmp;
	char	*home;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '~' && cmd[i][1] != '~')
		{
			tmp = cmd[i];
			home = get_var("HOME", &env);
			cmd[i] = ft_strjoin(home, cmd[i] + 1);
			ft_strdel(&home);
			ft_strdel(&tmp);
		}
		else
			cmd[i] = dollar_doer(cmd[i], env);
		i++;
	}
}

t_cmd	*well_you_know(char **cmd, t_cmd **lst, int *t, t_holder x)
{
	t_cmd	*head;
	t_cmd	*predictor;
	char	**kratos;
	int		i;

	i = 0;
	while (cmd[i])
	{
		kratos = ft_strsplit(cmd[i], -1);
		tilde_fix(kratos, x.head_ref);
		if (*t == 0)
			head = *lst;
		not_known_as_if(kratos, &(*lst), &(*t));
		if (!((*lst)->next = (t_cmd*)malloc(sizeof(t_cmd))))
			return (0);
		predictor = (*lst);
		(*lst) = (*lst)->next;
		ft_free2d(kratos);
		i++;
	}
	predictor->next = NULL;
	free(*lst);
	return (head);
}

t_cmd	*last_splice(char **data, t_env *env, t_alias *alias)
{
	t_cmd		*lst;
	t_cmd		*head;
	int			t;
	t_holder	x;

	if (!(lst = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	t = 0;
	x.head_ref = env;
	x.aliases = alias;
	head = well_you_know(data, &lst, &t, x);
	return (head);
}
