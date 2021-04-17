/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:26:48 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 17:47:36 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_walls(t_recup *recup)
{
	int	i;

	i = 0;
	while (i < recup->nblines)
	{
		if (recup->map[i][0] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < recup->nblines)
	{
		if (recup->map[i][recup->sizelines - 1] != '1')
			return (1);
		i++;
	}
	if (ft_walls_util(recup->map[0]) == 1)
		return (1);
	if (ft_walls_util(recup->map[recup->nblines - 1]) == 1)
		return (1);
	return (0);
}

int		ft_copy_map(char *str, t_recup *recup)
{
	static int	i = 0;
	int 		j;

	j = 0;
	recup->map[i] = NULL;
	if (!(recup->map[i] = malloc(sizeof(char) * (recup->sizelines + 1))))
		return (0);
	while (str[j] != '\0')
	{
		if (ft_start(str[j], recup, i, j) == 1)
			recup->map[i][j] = '0';
		else if (str[j] = ' ')
			recup->map[i][j] = '0';
		else
			recup->map[i][j] = str[j];
		j++;
	}
	while (j <= (recup->sizelines - 1))
	{
		recup->map[i][j] = '1';
		j++;
	}
	recup->map[i][j] = '\0';
	i++;
	return (0);
}

int		ft_is_map(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n' \
					&& str[i] != '\t')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_map(char *str, t_recup *recup)
{
	int			i;
	static int	snblines = 0;
	static int	ssizelines = 0;

	i = 0;
	if (ft_is_map(str) == 1)
	{
		if ((i = ft_strlen(str) > ssizelines)
			ssizelines = i;
		snblines = snblines + 1;
	}
	recup->nblines = snblines;
	recup->sizelines = ssizelines;
}