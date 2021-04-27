/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 09:07:13 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/17 09:09:13 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_map(char const *s, char (*f)(char))
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (NULL);
	if (f)
	{
		i = 0;
		while (*s)
			new[i++] = (*f)(*s++);
	}
	return (new);
}
