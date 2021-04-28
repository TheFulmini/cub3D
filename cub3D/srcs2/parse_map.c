/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:55:59 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:00 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**copy_map(t_data *d, t_pars *pars, char **map, int nb_lines)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = malloc(nb_lines * sizeof(char *));
	if (new_map == NULL)
		error_exit("Memory allocation error!", d, pars, 0);
	i = 0;
	while (i < nb_lines - 2)
	{
		new_map[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (new_map[i] == NULL)
			error_exit("Memory allocation error!", d, pars, new_map);
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i++][j] = 0;
	}
	new_map[i] = 0;
	new_map[i + 1] = 0;
	error_exit(NULL, NULL, NULL, map);
	return (new_map);
}

void	parse_map(t_data *d, t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	d->ret = 1;
	while (d->ret > 0 && !is_empty_line(d->line))
	{
		if (d->line && i != 0)
			free(d->line);
		if (i != 0)
			d->ret = get_next_line(d->fd, &d->line);
		pars->map = copy_map(d, pars, pars->map, i + 2);
		pars->map[i] = malloc(sizeof(char) * (ft_strlen(d->line) + 1));
		if (!pars->map[i])
			error_exit("Memory allocation error!", d, pars, 0);
		j = -1;
		while (d->line[++j])
			pars->map[i][j] = d->line[j];
		pars->map[i++][j] = 0;
		if (d->ret == 0)
			pars->map[i] = 0;
	}
	free(d->line);
	d->line = NULL;
}

void	add_sprite_pos(t_pars *p, int i, int j)
{
	t_sprite	*new_sprite;
	static int	n;
	int			k;

	new_sprite = malloc(sizeof(t_sprite) * (n + 1));
	k = 0;
	while (k < n)
	{
		new_sprite[k].x = p->sprite_tab[k].x;
		new_sprite[k].y = p->sprite_tab[k].y;
		k++;
	}
	new_sprite[k].x = i + 0.5;
	new_sprite[k].y = j + 0.5;
	if (p->sprite_tab)
		free(p->sprite_tab);
	p->sprite_tab = new_sprite;
	p->nb_of_sprites = n + 1;
	n++;
}

void	check_valid_map_char(t_data *d, t_pars *p, int i, int j)
{
	if (p->map[i][j] == 'N' || p->map[i][j] == 'S' || p->map[i][j] == 'E'
		|| p->map[i][j] == 'W')
	{
		p->dir = p->map[i][j];
		p->pos_x = i + 0.5;
		p->pos_y = j + 0.5;
	}
	if (p->map[i][j] == '2')
		add_sprite_pos(p, i, j);
	if (!is_space(p->map[i][j]) && p->map[i][j] != 'E' && p->map[i][j] != 'W'
		&& p->map[i][j] != 'N' && p->map[i][j] != 'S' && !(p->map[i][j] >= '0'
		&& p->map[i][j] <= '2'))
		error_exit("Alien character in map!", d, p, 0);
	if (p->map[i][j] == '0' || p->map[i][j] == '2' || p->map[i][j] == 'W'
			|| p->map[i][j] == 'N' || p->map[i][j] == 'S'
			|| p->map[i][j] == 'E')
	{
		if (j == 0 || j == (int)ft_strlen(p->map[i]) - 1 || i == 0
			|| p->map[i + 1] == 0 || j >= (int)ft_strlen(p->map[i + 1]))
			error_exit("Map is invalid!", d, p, 0);
		if (is_space(p->map[i + 1][j]) || is_space(p->map[i - 1][j])
				|| is_space(p->map[i][j + 1]) || is_space(p->map[i][j - 1]))
			error_exit("Map is invalid!", d, p, 0);
	}
}

void	is_valid_map(t_data *d, t_pars *pars)
{
	int		i;
	int		j;
	int		count_pos;

	i = 0;
	count_pos = 0;
	if (pars->map == NULL)
		error_exit("Invalid map!", d, pars, 0);
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (pars->map[i][j] == 'N' || pars->map[i][j] == 'S'
				|| pars->map[i][j] == 'E' || pars->map[i][j] == 'W')
				count_pos++;
			if (count_pos > 1)
				error_exit("More than one 'NSEW' in map!", d, pars, 0);
			check_valid_map_char(d, pars, i, j);
			j++;
		}
		i++;
	}
	if (count_pos != 1)
		error_exit("NSEW error in map!", d, pars, 0);
}
