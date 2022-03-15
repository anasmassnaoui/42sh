/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:21:32 by aariss            #+#    #+#             */
/*   Updated: 2020/01/31 13:59:16 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_STRUCT_H
# define HISTORY_STRUCT_H

typedef struct			s_history
{
	int					nb;
	char				*history;
	struct s_history	*next;
}						t_history;

typedef struct			s_all_hist
{
	t_history			*lst;
	t_history			*tmp;
	char				*path;
	int					fp;
	int					index;
	int					num;
	int					x;
	int					t;
	int					first;
	char				*tmp_str;
	char				*sub_str;

}						t_all_hist;

#endif
