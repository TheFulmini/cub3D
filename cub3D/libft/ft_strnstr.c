/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:58:30 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/17 10:09:26 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	if (*s2)
	{
		i = 0;
		while (s1[i] && i < len)
		{
			if (s1[i] == s2[0])
			{
				j = 1;
				while (i + j < len && s2[j] && s1[i + j] == s2[j])
					j++;
				if (s2[j] == '\0')
					return ((char*)&s1[i]);
			}
			i++;
		}
		return (0);
	}
	return ((char *)s1);
}
