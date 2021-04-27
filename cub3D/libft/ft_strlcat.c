/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:58:30 by afulmini          #+#    #+#             */
/*   Updated: 2020/08/23 16:20:45 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	result;
	size_t	size_dest;

	result = ft_strlen(src);
	size_dest = 0;
	while (dst[size_dest] && size > size_dest)
		size_dest++;
	i = 0;
	while (src[i] && size > size_dest && i < (size - size_dest - 1))
	{
		dst[size_dest + i] = src[i];
		i++;
	}
	if (size > size_dest)
		dst[size_dest + i] = '\0';
	result += size_dest;
	return (result);
}
