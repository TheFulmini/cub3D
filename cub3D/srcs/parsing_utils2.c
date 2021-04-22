/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:00:34 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 19:30:52 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_empty_line(char *line)
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

void	check_color_format(t_data *d, t_parse *pars)
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
			error_exit("Incorrect character in the color format.", d, pars, 0);
		if (is_digit(d->line[i]) && (d->line[i + 1] == ','
				|| is_space(d->line[i + 1]) || d->line[i + 1] == 0))
			nb_of_colors++;
		if (d->line[i++] == ',')
			commas++; 
	}
	if (commas != 2)
		error_exit("Wrong number of comma arguments.", d, pars, 0);
	if (nb_of_colors != 3)
		error_exit("Wrong number of rgb arguments.", d, pars, 0);
}

void	set_bool_elem(t_data *d, t_elems *elems, t_parse *pars)
{
	if (ft_strncmp(d->id, "NO") == 0 && !elems->no_text)
		elems->no_text = 1;
	else if (ft_strncmp(d->id, "SO") == 0 && !elems->so_text)
		elems->so_text = 1;
	else if (ft_strncmp(d->id, "EA") == 0 && !elems->ea_text)
		elems->ea_text = 1;
	else if (ft_strncmp(d->id, "WE") == 0 && !elems->we_text)
		elems->we_text = 1;
	else if (ft_strncmp(d->id, "F") == 0 && !elems->floor_col)
		elems->floor_col = 1;
	else if (ft_strncmp(d->id, "C") == 0 && !elems->ceiling_col)
		elems->ceiling_col = 1;
	else
		error_exit("Invalid identifier", d, pars, 0);
}

int		all_elems_found(t_elems elems)
{
		if (elems.res == 0)
		return (0);
	if (elems.no_text == 0)
		return (0);
	if (elems.so_text == 0)
		return (0);
	if (elems.we_text == 0)
		return (0);
	if (elems.ea_text == 0)
		return (0);
	if (elems.spr_text == 0)
		return (0);
	if (elems.floor_col == 0)
		return (0);
	if (elems.ceiling_col == 0)
		return (0);
	return (1);
}

void	get_res(t_data *d, t_parse *pars, t_elems *elems)
{
	int	i;

	i = 0;
	if (count_arg(d->line) != 2)
		error_exit("Invalid number of arguments for Resolution.". d, pars, 0);
	while (is_space(d->line[i]) && d->line[i])
		i++;
	while (is_upper(d->line[i]) && d->line[i])
		i++;
	i--;
	while (d->line[i++])
		if (!is_digit(d->line[i]) && d->line[i])
			error_exit("Incorrect character in Resolution argument.", d, pars, 0);
	i = 0;
	while (!is_digit(d->line[i]))
		i++;
	pars->screen_width = atoi(d->line + i);
	if (pars->screen_width <= 0)
		error_exit("Invalid screen width!", d, pars, 0);
	while (!is_space(d->line[i]))
		i++;
	pars->screen_heigth = atoi(d->line + i);
	if (pars->screen_heigth <= 0)
		error_exit("Invalid screen heigth!", d, pars, 0);
	elems->res = 1;
}