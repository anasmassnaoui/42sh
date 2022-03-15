/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:50:13 by mhouiri           #+#    #+#             */
/*   Updated: 2019/12/21 15:51:47 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_STRUCT_H
# define LINE_STRUCT_H

typedef struct			s_line
{
	char				*str;
	char				*tmp_str;
	char				*cmd;
	int					col;
	int					row;
	int					curs;
	int					in;
	int					my_in;
	char				*copy;
	int					x;
	int					msg_size;
	int					index_history;
	int					mode_select;

	struct s_names		*names;
	char				*ground;
	char				*hint;
	int					mode_auto;
	int					tmp_curs;

}						t_line;

#endif
