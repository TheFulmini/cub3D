/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:58:30 by afulmini          #+#    #+#             */
/*   Updated: 2020/08/23 16:20:45 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *strdest;
	unsigned char *strsrc;

	strdest = (unsigned char *)dst;
	strsrc = (unsigned char *)src;
	if (dst == src)
		return (NULL);
	if (dst == NULL && src == NULL)
		return (NULL);
	if (strdest > strsrc)
		while (len > 0)
		{
			strdest[len - 1] = strsrc[len - 1];
			len--;
		}
	else
		while (len--)
			*strdest++ = *strsrc++;
	return (dst);
}
