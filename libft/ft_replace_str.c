/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:54:46 by aariss            #+#    #+#             */
/*   Updated: 2020/01/17 18:54:48 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_till_index(char *str, int index)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * index + 1)))
		return (NULL);
	while (i < index)
	{
		ptr[i] = str[i];
		i += 1;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*copy_from_index(char *str, size_t index)
{
	char	*ptr;
	int		i;
	int		j;

	j = (ft_strlen(str) - index + 1);
	if (j <= 0)
		j = 1;
	if (!(ptr = (char *)malloc(sizeof(char) * (j))))
		return (NULL);
	i = 0;
	while (index < ft_strlen(str))
	{
		ptr[i] = str[index];
		index += 1;
		i += 1;
	}
	ptr[i] = '\0';
	return (ptr);
}

int		*match(char *str, char *needle, int *i)
{
	int		k;
	size_t	j;
	int		start;
	int		*map;

	j = 0;
	k = 0;
	start = *i;
	map = (int *)malloc(sizeof(int) * 2);
	while (str[k] == needle[j] && str[k])
	{
		k += 1;
		j += 1;
	}
	if (j == ft_strlen(needle))
	{
		map[0] = start;
		map[1] = (*i) + k;
		return (map);
	}
	return (NULL);
}

int		*map_string(char *str, char *needle)
{
	int	i;
	int	*map;

	i = 0;
	while (str[i])
	{
		if (str[i] == needle[0])
			if ((map = match(str + i, needle, &i)) != NULL)
				break ;
		i += 1;
	}
	return (map);
}

char	*ft_replace_str(char *str, char *find, char *replace)
{
	int		*map;
	char	*after;
	char	*before;
	char	*first_merge;
	char	*second_merge;

	if (!str || !find || !(map = map_string(str, find)))
		return (NULL);
	before = copy_till_index(str, map[0]);
	after = copy_from_index(str, map[1]);
	first_merge = ft_strjoin(before, replace);
	second_merge = ft_strjoin(first_merge, after);
	ft_strdel(&before);
	ft_strdel(&after);
	ft_strdel(&first_merge);
	return (second_merge);
}
