/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:56:07 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:07 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_values(t_data *d, t_pars *pars)
{
	pars->n_path = NULL;
	pars->s_path = NULL;
	pars->e_path = NULL;
	pars->w_path = NULL;
	pars->sprite_path = NULL;
	pars->map = NULL;
	d->line = NULL;
	d->id = NULL;
	d->ret = 1;
	pars->sprite_tab = NULL;
	pars->nb_of_sprites = 0;
	pars->save_arg = 0;
}

void	init_elems(t_elems *elems)
{
	elems->res = 0;
	elems->no_text = 0;
	elems->so_text = 0;
	elems->we_text = 0;
	elems->ea_text = 0;
	elems->spr_text = 0;
	elems->floor_col = 0;
	elems->ceiling_col = 0;
}

char	*get_identifier(t_data *d)
{
	int		i;
	int		j;

	i = 0;
	while (is_space(d->line[i]) && d->line[i])
		i++;
	j = i;
	while (!is_space(d->line[j]) && d->line[j])
		j++;
	d->id = malloc(sizeof(char) * (j - i + 1));
	if (d->id == NULL)
		error_exit("Memory allocation error!", d, 0, 0);
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
		error_exit("Map file must end with \".cub\"!", 0, 0, 0);
	d->fd = open(map_arg, O_WRONLY);
	if (d->fd == -1)
		error_exit("Couldn't find map file!", d, 0, 0);
	close(d->fd);
	d->fd = open(map_arg, O_RDONLY);
	if (d->fd == -1)
		error_exit("Couldn't find map argument!", d, 0, 0);
}

int	count_args(char *line)
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
