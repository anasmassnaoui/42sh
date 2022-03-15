/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 11:47:47 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/16 15:44:17 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char			*search_in_hist(t_history *tmp, char *ptr, int index)
{
	if (index > len_list(tmp) || index < 0)
		return (ft_strdup(last_node(tmp)));
	while (tmp)
	{
		if (tmp->nb == index || !ft_strncmp(tmp->history, ptr, ft_strlen(ptr)))
			return (tmp->history);
		else
			tmp = tmp->next;
	}
	return (ft_strdup(ptr));
}

char			*insert_in_line(char *str, char *substr, int start, int end)
{
	int			i;
	char		*s1;
	char		*s2;
	char		*tmp;
	char		*line;

	s1 = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	s2 = ft_strdup(str + end);
	i = 0;
	while (i < start)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = '\0';
	tmp = s1;
	s1 = ft_strjoin(s1, substr);
	ft_strdel(&tmp);
	line = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	ft_strdel(&str);
	return (line);
}

char			*fc_s(t_history *tmp, char **arr)
{
	int			i;
	char		*l_node;
	char		*str;

	str = NULL;
	l_node = ft_strdup(last_node(tmp));
	i = 0;
	while (last_node(tmp)[i])
	{
		if (!ft_strncmp(last_node(tmp) + i, arr[0], ft_strlen(arr[0])))
		{
			str = insert_in_line(l_node, arr[1], i, i + ft_strlen(arr[0]));
			ft_free_tab2(arr);
			return (str);
		}
		else
			i++;
	}
	ft_strdel(&l_node);
	return (0);
}

char			*middle_lst(char *str, char **arr)
{
	int			i;
	char		*str2;

	str2 = NULL;
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str + i, arr[0], ft_strlen(arr[0])))
		{
			str2 = insert_in_line(str, arr[1], i, i + ft_strlen(arr[0]));
			ft_free_tab2(arr);
			return (str2);
		}
		else
			i++;
	}
	ft_free_tab2(arr);
	return (str);
}

char			*search_replace(char **ptr, t_history *tmp)
{
	char		**arr;
	char		*str;

	arr = ft_strsplit(ptr[2], '=');
	if (ptr[3] == NULL)
	{
		if ((str = fc_s(tmp, arr)))
			return (str);
	}
	else
	{
		if (ft_atoi(ptr[3]) > len_list(tmp))
			return (fc_s(tmp, arr));
		while (tmp)
		{
			if (tmp->nb == ft_atoi(ptr[3])
			|| !ft_strncmp(tmp->history, ptr[3], ft_strlen(ptr[3])))
				return (middle_lst(tmp->history, arr));
			else
				tmp = tmp->next;
		}
		return (ptr[3]);
	}
	ft_free_tab2(arr);
	return (ft_strdup(last_node(tmp)));
}
