/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:56:36 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/08 17:57:55 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnchar(const char c, const int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
	return (i);
}
