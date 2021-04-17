/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:55:47 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 16:38:23 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_strlen_parse(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (1);
}

int		ft_charinstr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_start(char c, t_recup *recup, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (recup->start != 'x')
			ft_error(recup, "More than one player in the map");
		recup->start = c;
		recup->dx = i;
		recup->dy = j;
		return (1);
	}
	return (0);
}

int		ft_walls_util(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 1)
			return (1);
		i++;
	}
	return (0);
}

void		ft_init(t_recup *recup)
{
	recup->NO = NULL;
	recup->SO = NULL;
	recup->EA = NULL;
	recup->WE = NULL;
	recup->S = NULL;
	recup->F = 0;
	recup->C = 0;;
	recup->Rx = 0;
	recup->Ry = 0;
	recup->nblines = 0;
	recup->sizelines = 0;
	recup->map = NULL;
	recup->dx = 0;
	recup->dy = 0;
	recup->start = 'x';
	recup->indicator1 = 0;
	recup->data.img = NULL;
	recup->texture[0].img = NULL;
	recup->texture[0].img = NULL;
	recup->texture[0].img = NULL;
	recup->texture[0].img = NULL;
	recup->texture[0].img = NULL;
	//recup->map = NULLL;
	recup->data.win_ptr = NULL; // ???????????????????
	recup->s.order = NULL; // ???????????????
	recup->s.distance = NULL; // ?????????????????
}
