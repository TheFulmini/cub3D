/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:43:37 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/29 15:23:55 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_values(t_data *d, t_parse *p)
{
	p->no_path = NULL;
	p->so_path = NULL;
	p->we_path = NULL;
	p->ea_path = NULL;
	p->sprite_path = NULL;
	p->map = NULL;
	d->line = NULL;
	d->id = NULL;
	d->ret = 1;
	p->sprite_tab = NULL;
	p->nb_sprites = 0;
	p->save = 0;
}

void	init_elems(t_elems *e)
{
	e->res = 0;
	e->no_text = 0;
	e->so_text = 0;
	e->we_text = 0;
	e->ea_text = 0;
	e->spr_text = 0;
	e->floor_col = 0;
	e->ceiling_col = 0;
}

char	*get_identifier(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (is_space(d->line[i]) && d->line[i])
		i++;
	j = i;
	while (!is_space(d->line[j]) && d->line[j])
		j++;
	d->id = malloc(sizeof(char) * (j - i + 1));
	if (d->id == NULL)
		error_exit("Memory not properly allocated.", d, 0, 0);
	j = i;
	i = 0;
	while (!is_space(d->line[j]) && d->line[j])
	{
		d->id[i] = d->line[j];
		i++;
		j++;
	}
	d->id[i] = 0;
	return (d->id);
}

void	get_fd(char *map_arg, char *ext, t_data *d)
{
	int	i;

	i = 0;
	while (map_arg[i])
		i++;
	if (ft_strcmp(map_arg + i - 4, ext))
		error_exit("Map file must be \".cub\" format.", 0, 0, 0);
	d->fd = open(map_arg, O_WRONLY);
	if (d->fd == -1)
		error_exit("Map file not found.", d, 0, 0);
	close(d->fd);
	d->fd = open(map_arg, O_RDONLY);
	if (d->fd == -1)
		error_exit("No map argument given.", d, 0, 0);
}

int	count_arg(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (is_space(line[i]) && line[i])
		i++;
	while (is_upper(line[i]) && line[i])
		i++;
	while (is_space(line[i]) && line[i])
		i++;
	while (line[i])
	{
		while (!is_space(line[i]) && line[i])
			i++;
		count++;
		while (is_space(line[i]) && line[i])
			i++;
	}
	return (count);
}
