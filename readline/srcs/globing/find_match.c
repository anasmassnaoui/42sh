/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:12:11 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 15:56:17 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

char	**range_maker(char *hint)
{
	char	**ptr;
	char	*str;
	char	*head;

	hint++;
	if (!(str = (char*)malloc(sizeof(char) * special_count(hint))))
		return (NULL);
	head = str;
	while (*hint && *hint != ']')
	{
		if (ft_isalnum(*hint) && *(hint + 1) == '-')
			*str++ = ';';
		*str++ = *hint++;
	}
	ptr = ft_strsplit(head, ';');
	return (ptr);
}

void	question_match(char **string, char **hint)
{
	*string += 1;
	*hint += 1;
}

void	after_asterisk(char **string, char **hint)
{
	while (**string && **string != **hint)
	{
		if (**hint != '?' && **hint != '[')
			*string += 1;
		if (**hint == '?')
		{
			question_match(string, hint);
		}
		else if (**hint == '[')
			break ;
	}
}

int		asterisk_match(char **string, char **hint)
{
	int	voyeur;

	voyeur = (int)ft_strlen(*string) - (int)seer((*hint + 1));
	if (voyeur < 0)
		return (0);
	while (**hint == '*' && **hint)
	{
		*hint += 1;
	}
	after_asterisk(string, hint);
	return (1);
}

int		match_glob(char *string, char *hint)
{
	int v;

	v = 0;
	while (42)
	{
		if (*hint == 92 && is_wild_token(*(hint + 1)))
			return (0);
		else if (*hint == '*')
			(!asterisk_match(&string, &hint)) ? v = 1 : 0;
		else if (*hint == '?')
			question_match(&string, &hint);
		else if (*hint == '[')
			(!bracket_match(&string, &hint)) ? v = 1 : 0;
		else if (*hint != '*' && *hint != '?'
				&& *hint != '[' && (*string == *hint))
			characters_match(&string, &hint);
		else
			return (0);
		if (v)
			return (0);
		if (!*string && !*hint)
			break ;
	}
	return (1);
}
