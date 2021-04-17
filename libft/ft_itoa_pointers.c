/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_pointers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:06:05 by afulmini          #+#    #+#             */
/*   Updated: 2021/03/19 14:50:14 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_pointers(unsigned long int nb, int base)
{
	char				*str;
	unsigned long int	tmp;
	int					len;

	tmp = nb;
	len = 1;
	while (tmp / base > 0)
	{
		tmp = tmp / base;
		len++;
	}
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if (nb % base < 10)
			str[len] = nb % base + '0';
		else
			str[len] = nb % base + 'a' - 10;
		nb = nb / base;
	}
	return (str);
}
