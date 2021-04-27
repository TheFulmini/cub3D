/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:58:30 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/17 10:07:50 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

char			*ft_strndup(const char *s, size_t n)
{
	char	*map;
	size_t	i;

	if (!(map = malloc(sizeof(char) * (n + 1))))
		return (map);
	i = 0;
	while (i < n)
	{
		map[i] = s[i];
		i++;
	}
	map[i] = '\0';
	return (map);
}

static void		*destroy_strs(char **strs)
{
	int		i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(res = malloc(sizeof(char*) * (count(s, c) + 1))))
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (!(res[j++] = ft_strndup(s, i)))
			return (destroy_strs(res));
		s += i;
	}
	res[j] = 0;
	return (res);
}
