/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:00:34 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/29 15:23:00 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_empty(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_color_format(t_data *d, t_parse *p)
{
	int	i;
	int	commas;
	int	nb_of_colors;

	i = 0;
	commas = 0;
	nb_of_colors = 0;
	while (is_space(d->line[i]))
		i++;
	while (is_upper(d->line[i]))
		i++;
	while (d->line[i])
	{
		if (!is_digit(d->line[i]) && !is_space(d->line[i]) && d->line[i] != ',')
			error_exit("Incorrect character in the color format.", d, p, 0);
		if (is_digit(d->line[i]) && (d->line[i + 1] == ','
				|| is_space(d->line[i + 1]) || d->line[i + 1] == 0))
			nb_of_colors++;
		if (d->line[i++] == ',')
			commas++;
	}
	if (commas != 2)
		error_exit("Wrong number of comma arguments.", d, p, 0);
	if (nb_of_colors != 3)
		error_exit("Wrong number of rgb arguments.", d, p, 0);
}

void	set_bool_elem(t_data *d, t_elems *e, t_parse *p)
{
	if (ft_strcmp(d->id, "NO") == 0 && !e->no_text)
		e->no_text = 1;
	else if (ft_strcmp(d->id, "SO") == 0 && !e->so_text)
		e->so_text = 1;
	else if (ft_strcmp(d->id, "EA") == 0 && !e->ea_text)
		e->ea_text = 1;
	else if (ft_strcmp(d->id, "WE") == 0 && !e->we_text)
		e->we_text = 1;
	else if (ft_strcmp(d->id, "F") == 0 && !e->floor_col)
		e->floor_col = 1;
	else if (ft_strcmp(d->id, "C") == 0 && !e->ceiling_col)
		e->ceiling_col = 1;
	else if (ft_strcmp(d->id, "S") == 0 && !e->spr_text)
		e->spr_text = 1;
	else
		error_exit("Invalid identifier", d, p, 0);
}

int	all_elements_found(t_elems e)
{
	if (e.res == 0)
		return (0);
	if (e.no_text == 0)
		return (0);
	if (e.so_text == 0)
		return (0);
	if (e.we_text == 0)
		return (0);
	if (e.ea_text == 0)
		return (0);
	if (e.spr_text == 0)
		return (0);
	if (e.floor_col == 0)
		return (0);
	if (e.ceiling_col == 0)
		return (0);
	return (1);
}

void	get_res(t_data *d, t_parse *p, t_elems *e)
{
	int	i;

	i = 0;
	if (count_arg(d->line) != 2)
		error_exit("Invalid number of arguments for Resolution.", d, p, 0);
	while (is_space(d->line[i]) && d->line[i])
		i++;
	while (is_upper(d->line[i]) && d->line[i])
		i++;
	i--;
	while (d->line[++i])
		if (!is_digit(d->line[i]) && !is_space(d->line[i]))
			error_exit("Incorrect character in RES argument.", d, p, 0);
	i = 0;
	while (!is_digit(d->line[i]))
		i++;
	p->screen_width = atoi(d->line + i);
	if (p->screen_width <= 0)
		error_exit("Invalid screen width!", d, p, 0);
	while (!is_space(d->line[i]))
		i++;
	p->screen_height = atoi(d->line + i);
	if (p->screen_height <= 0)
		error_exit("Invalid screen height!", d, p, 0);
	e->res = 1;
}
