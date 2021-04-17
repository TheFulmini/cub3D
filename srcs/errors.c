/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:51:36 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 17:13:12 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_verify_errors(t_recup *recup)
{
	if (ft_walls(recup) == 1)
		ft_error(recup, "Map not closed\n");
	if (recup->start == 'x')
		ft_error(recup, "No player on the map\n");
	if (recup->indicator1 != 6)
		ft_error(recup, "Invalid data for F or C\n");
}

void		ft_error(t_recup *recup, char *str)
{
	int i;

	i = -1;
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));

/* free textures */
	if (recup->NO)
		free(recup->NO);
	if (recup->SO)
		free(recup->SO);
	if (recup->EA)
		free(recup->EA);
	if (recup->WE)
		free(recup->WE);

/* free the map */
	if (recup->map)
	{
		while (++i < recup->nblines)
			free(recup->map[i]);
	}
	if (recup->map)
		free(recup->map);

/*free sprite order, sprite distans and sprite position */
	if (recup->s.order)
		free(recup->s.order);
	if (recup->s.distance)
		free(recup->s.distance);
	

	ft_exit(recup);
}

int		ft_exit(t_recup *recup)
{
	
}