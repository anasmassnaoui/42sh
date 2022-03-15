/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:33:42 by myamani           #+#    #+#             */
/*   Updated: 2020/02/05 20:14:46 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*replace_espace(char *value1)
{
	char	*value;
	int		i;

	i = 0;
	value = (char *)ft_memalloc(sizeof(char) * (ft_strlen(value1) + 1));
	while (value1[i])
	{
		value[i] = value1[i];
		value[i] = (value1[i] == -1) ? ' ' : value1[i];
		i++;
	}
	value[i] = '\0';
	ft_strdel((void *)&value1);
	return (value);
}

void	print_export1(t_env **head_ref, char **token, t_env *current, int i)
{
	int		found;
	char	*tmp;

	while (token[i])
	{
		found = 0;
		tmp = ft_strjoin(token[i], "=");
		current = *head_ref;
		while (current)
		{
			if (!ft_strcmp(current->var, tmp) && ++found)
				ft_dprintf(1, "export %s%s\n", current->var, current->value);
			current = current->next;
		}
		if (found == 0 && (get_set_holder(false, NULL)->last_status = 1))
		{
			ft_dprintf(2, "export: no such variable: %s\n", token[i]);
			get_set_holder(false, NULL)->last_status = 1;
		}
		ft_strdel((void *)&tmp);
		i++;
	}
}

void	ft_putvalue(char *value)
{
	int i;

	i = 0;
	ft_putchar('\"');
	while (value[i])
	{
		(value[i] == '"') ? ft_putchar('\\') : 0;
		ft_putchar(value[i]);
		i++;
	}
	ft_putchar('\"');
}

void	print_export(t_env **head_ref, char **token)
{
	t_env	*current;
	int		i;

	i = 2;
	current = *head_ref;
	if (token[2] == NULL)
		while (current)
		{
			if (current->env && current->var)
			{
				ft_putstr("export ");
				(current->var) ? ft_printf("%s=", current->var, 1) : 0;
				(current->value) ? ft_printf("\"%s\"", current->value) : 0;
				ft_putendl_fd("", 1);
			}
			current = current->next;
		}
	else
		print_export1(head_ref, token, current, i);
}
