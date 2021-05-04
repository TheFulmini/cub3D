/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:36:30 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/04 11:38:33 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**copy_map(t_data *d, t_parse *p, char **map, int nb_lines)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = malloc(nb_lines * sizeof(char *));
	if (new_map == NULL)
		error_exit("Error. Not enough memory to allocate.", d, p, 0);
	i = 0;
	while (i < nb_lines - 2)
	{
		new_map[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (new_map[i] == NULL)
			error_exit("Error. Not enough memory to allocate.", d, p, 0);
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

void	map_parsing(t_data *d, t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	d->ret = 1;
	while (d->ret > 0 && !is_empty(d->line))
	{
		if (d->line && i != 0)
			free(d->line);
		if (i != 0)
			d->ret = get_next_line(d->fd, &d->line);
		p->map = copy_map(d, p, p->map, i + 2);
		p->map[i] = malloc(sizeof(char) * (ft_strlen(d->line) + 1));
		if (!p->map[i])
			error_exit("Error, Not enough free memory to allocate.", d, p, 0);
		j = -1;
		while (d->line[++j])
			p->map[i][j] = d->line[j];
		p->map[i++][j] = 0;
		if (d->ret == 0)
			p->map[i] = 0;
	}
	free(d->line);
	d->line = NULL;
}

void	add_sprite_pos(t_parse *p, int i, int j)
{
	t_sprites	*new_sprite;
	static int	n;
	int			k;

	new_sprite = malloc(sizeof(t_sprites) * (n + 1));
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
	p->nb_sprites = n + 1;
	n++;
}

void	check_map_char(t_data *d, t_parse *p, int i, int j)
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
		error_exit("Why is there an Alien character in map!", d, p, 0);
	if (p->map[i][j] == '0' || p->map[i][j] == '2' || p->map[i][j] == 'N'
		|| p->map[i][j] == 'S' || p->map[i][j] == 'E'
		|| p->map[i][j] == 'W')
	{
		if (j == 0 || j == (int)ft_strlen(p->map[i]) - 1 || i == 0
			|| p->map[i + 1] == 0 || j >= (int)ft_strlen(p->map[i + 1]))
			error_exit("Invalid map.", d, p, 0);
		if (is_space(p->map[i + 1][j]) || is_space(p->map[i - 1][j])
			|| is_space(p->map[i][j + 1]) || is_space(p->map[i][j - 1]))
			error_exit("Invalid map.", d, p, 0);
	}
}

void	check_valid_map(t_data *d, t_parse *p)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	if (p->map == NULL)
		error_exit("Invalid map.", d, p, 0);
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S'
				|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
				pos++;
			if (pos > 1)
				error_exit("More than one player on the map.", d, p, 0);
			check_map_char(d, p, i, j);
			j++;
		}
		i++;
	}
	if (pos != 1)
		error_exit("No player available for game.", d, p, 0);
}
