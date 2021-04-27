/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:11:47 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/16 18:15:11 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstsplit(char const *s, char c)
{
	t_list	*dest;
	char	**tab;

	dest = NULL;
	tab = ft_split(s, c);
	if (tab)
	{
		while (*tab)
		{
			ft_lstadd_back(&dest, ft_lstnew(*tab));
			tab++;
		}
	}
	return (dest);
}
