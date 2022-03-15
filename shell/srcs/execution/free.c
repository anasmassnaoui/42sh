/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:11:50 by aariss            #+#    #+#             */
/*   Updated: 2020/02/14 23:23:43 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_info(t_info *lst)
{
	if (lst == NULL)
		return ;
	free_info(lst->next);
	if (lst->file)
		ft_strdel(&lst->file);
	free(lst);
	lst = NULL;
}

void	free_main_lst(t_cmd *lst)
{
	if (lst == NULL)
		return ;
	free_main_lst(lst->next);
	free_info(lst->red);
	ft_free2d(lst->cmd);
	free(lst);
	lst = NULL;
}

void	free_list_env(t_env **head_ref)
{
	t_env	*current;

	if (*head_ref)
	{
		while (*head_ref && ((*head_ref)->env == 0 || (*head_ref)->env == 1))
		{
			current = *head_ref;
			*head_ref = (*head_ref)->next;
			(current->var) ? ft_strdel(&current->var) : 0;
			(current->value) ? ft_strdel(&current->value) : 0;
			(current->value_copy) ? ft_strdel(&current->value_copy) : 0;
			free(current);
			current = NULL;
		}
	}
}

void	free_list_mc(t__mc *lst)
{
	t__mc	*current;

	current = lst;
	while (lst)
	{
		current = lst;
		lst = lst->next;
		(current->cmd) ? ft_free2d(current->cmd) : 0;
		free(current);
		current = NULL;
	}
}
