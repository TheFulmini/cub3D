/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:59:07 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 19:11:03 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_parser(t_parse *pars)
{
	int	i;

	if (pars)
	{
		if (pars->no_path)
			free(pars->no_path);
		if (pars->so_path)
			free(pars->so_path);
		if (pars->ea_path)
			free(pars->ea_path);
		if (pars->we_path)
			free(pars->we_path);
		if (pars->sprite_path)
			free(pars->sprite_path);
		if (pars->sprite_tab)
			free(pars->sprite_tab);
		i = 0;
		if (pars->map)
		{
			while (pars->map[i])
				free(pars->map[i++]);
			free(pars->map);
		}
	}
}

void	error_exit(char *error_msg, t_data *d, t_parse *pars, char **map)
{
	int	i;

	if (d)
	{
		if (d->id)
			free(d->id);
		if(d->line)
			free(d->line);
		if (d->fd)
			close(d->fd);
	}
	if (pars)
		free_parser(pars);
	i = 0;
	if (map)
		while (map[i])
			free(map[i++]);
		free(map);
	if (error_msg)
	{
		printf("ERROR\n%s\n", error_msg);
		exit(0);
	}
}

void	check_map(t_data *d, t_parse *pars)
{
	d->line = NULL;
	d->id = NULL;
	while (is_empty_line(d->line) && d->ret > 0) //define function
	{
		free(d->line);
		d->ret = get_next_line(d->fd, &d->line);
	}
	if (d->ret < 0)
		error_exit("Problem reading the file.", d, pars, 0);
	parse_map(d, pars); // define function
	if (d->ret < 0)
		error_exit("Problem reading the file.", d, pars, 0);
	is_valid_map(d, pars); // define function
	pars->map[(int)pars->pos_x][(int)pars->pos_y] = '0';
	close(d->fd);
	if (pars->screen_width > 2880)
		pars->screen_width = 2880;
	if (pars->screen_heigth > 1490)
		pars->screen_heigth = 1490;
}

void	parsing(int argc, char **argv, t_parse *pars)
{
	t_data	d;

	init_values(&d, pars); //define function
	if (argc < 2 || argc > 3)
		error_exit("Invalid number of arguments.", 0, 0, 0);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			error_exit("Invalid 3rd argument.", 0, 0, 0);
		else
			pars->save_arg = 1;
	}
	get_fd(argv[1], ".cub", &d); // define function
	parse_elems(&d, pars); // define function
	check_map(&d, pars); 
}