/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:55:51 by amilis            #+#    #+#             */
/*   Updated: 2021/04/28 19:23:06 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_path2(t_data *d, t_pars *pars, char *path)
{
	int	fd;

	if (ft_strcmp(d->id, "NO") == 0)
		pars->n_path = path;
	if (ft_strcmp(d->id, "SO") == 0)
		pars->s_path = path;
	if (ft_strcmp(d->id, "EA") == 0)
		pars->e_path = path;
	if (ft_strcmp(d->id, "WE") == 0)
		pars->w_path = path;
	if (ft_strcmp(d->id, "S") == 0)
		pars->sprite_path = path;
	fd = open(path, O_WRONLY);
	if (fd < 0)
	{
		close(fd);
		error_exit("Invalid texture or sprite path!", d, pars, 0);
	}
}

void	get_path(t_data *d, t_pars *pars, t_elems *elems)
{
	int		i;
	char	*path;
	int		j;

	i = 0;
	if (count_args(d->line) != 1)
		error_exit("Path : invalid number of arguments", d, pars, 0);
	while (is_space(d->line[i]) && d->line[i])
		i++;
	while (is_upper(d->line[i]) && d->line[i])
		i++;
	while (is_space(d->line[i]) && d->line[i++])
		j = i;
	while (!is_space(d->line[i]) && d->line[i])
		i++;
	path = malloc(sizeof(char) * (i - j + 1));
	if (path == NULL)
		error_exit("Memory allocation error!", d, pars, 0);
	i = j;
	j = 0;
	while (!is_space(d->line[i]) && d->line[i])
		path[j++] = d->line[i++];
	path[j] = 0;
	get_path2(d, pars, path);
	set_bool_elem(d, elems, pars);
}

void	get_color(t_data *d, t_pars *pars, t_elems *elems)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	check_color_format(d, pars);
	while (!is_digit(d->line[i]))
		i++;
	r = ft_atoi(d->line + i);
	while (d->line[i] != ',')
		i++;
	i++;
	g = ft_atoi(d->line + i);
	while (d->line[i] != ',')
		i++;
	i++;
	b = ft_atoi(d->line + i);
	if (b < 0 || b > 255 || r < 0 || r > 255 || g < 0 || g > 255)
		error_exit("R, G or B was not in [0;255] range!", d, pars, 0);
	if (ft_strcmp(d->id, "C") == 0)
		pars->ceiling_color = 65536 * r + 256 * g + b;
	else
		pars->floor_color = 65536 * r + 256 * g + b;
	set_bool_elem(d, elems, pars);
}

void	get_elem(t_data *d, t_pars *pars, t_elems *elems)
{
	if (ft_strcmp(d->id, "R") == 0)
		get_res(d, pars, elems);
	else if (ft_strcmp(d->id, "NO") == 0)
		get_path(d, pars, elems);
	else if (ft_strcmp(d->id, "SO") == 0)
		get_path(d, pars, elems);
	else if (ft_strcmp(d->id, "WE") == 0)
		get_path(d, pars, elems);
	else if (ft_strcmp(d->id, "EA") == 0)
		get_path(d, pars, elems);
	else if (ft_strcmp(d->id, "S") == 0)
		get_path(d, pars, elems);
	else if (ft_strcmp(d->id, "F") == 0)
		get_color(d, pars, elems);
	else if (ft_strcmp(d->id, "C") == 0)
		get_color(d, pars, elems);
	else
		error_exit("Invalid identifier!", d, pars, 0);
}

void	parse_elements(t_data *d, t_pars *pars)
{
	int		ret;
	t_elems	elems;
	int		i;

	init_elems(&elems);
	ret = 1;
	i = 1;
	while (ret > 0 && !all_elems_found(elems))
	{
		ret = get_next_line(d->fd, &d->line);
		if (ret == -1)
			error_exit("Couldn't read file!", d, 0, 0);
		if (!is_empty_line(d->line) || (is_upper(d->line[0])))
		{
			d->id = get_identifier(d);
			get_elem(d, pars, &elems);
			if (d->id)
				free(d->id);
		}
		if (d->line)
			free(d->line);
	}
}
