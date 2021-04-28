/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:59:07 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/28 19:38:09 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_parser(t_parse *p)
{
	int	i;

	if (p)
	{
		if (p->no_path)
			free(p->no_path);
		if (p->so_path)
			free(p->so_path);
		if (p->ea_path)
			free(p->ea_path);
		if (p->we_path)
			free(p->we_path);
		if (p->sprite_path)
			free(p->sprite_path);
		if (p->sprite_tab)
			free(p->sprite_tab);
		i = 0;
		if (p->map)
		{
			while (p->map[i])
				free(p->map[i++]);
			free(p->map);
		}
	}
}

void	error_exit(char *error_msg, t_data *d, t_parse *p, char **map)
{
	int	i;

	if (d)
	{
		if (d->id)
			free(d->id);
		if (d->line)
			free(d->line);
		if (d)
			close(d->fd);
	}
	if (p)
		free_parser(p);
	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	if (error_msg)
	{
		printf("ERROR\n%s\n", error_msg);
		exit(0);
	}
}

void	check_map(t_data *d, t_parse *p)
{
	d->line = NULL;
	d->id = NULL;
	while (is_empty(d->line) && d->ret > 0)
	{
		free(d->line);
		d->ret = get_next_line(d->fd, &d->line);
	}
	if (d->ret < 0)
		error_exit("Problem reading the file.", d, p, 0);
	map_parsing(d, p);
	if (d->ret < 0)
		error_exit("Problem reading the file.", d, p, 0);
	check_valid_map(d, p);
	p->map[(int)p->pos_x][(int)p->pos_y] = '0';
	close(d->fd);
	if (p->screen_width > 2880)
		p->screen_width = 2880;
	if (p->screen_height > 1490)
		p->screen_height = 1490;
}

void	parsing(int argc, char **argv, t_parse *p)
{
	t_data	d;

	init_values(&d, p);
	if (argc < 2 || argc > 3)
		error_exit("Invalid number of arguments.", 0, 0, 0);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			error_exit("Invalid 3rd argument.", 0, 0, 0);
		else
			p->save = 1;
	}
	get_fd(argv[1], ".cub", &d);
	parse_elements(&d, p);
	check_map(&d, p);
}
