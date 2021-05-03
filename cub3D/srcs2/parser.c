/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:56:19 by amilis            #+#    #+#             */
/*   Updated: 2021/05/03 11:52:42 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_pars(t_pars *pars)
{
	int	i;

	if (pars)
	{
		if (pars->n_path)
			free(pars->n_path);
		if (pars->s_path)
			free(pars->s_path);
		if (pars->e_path)
			free(pars->e_path);
		if (pars->w_path)
			free(pars->w_path);
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

void	error_exit(char *error_msg, t_data *d, t_pars *pars, char **map)
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
	if (pars)
		free_pars(pars);
	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
	if (error_msg)
	{
		printf("Error\n%s\n", error_msg);
		exit(0);
	}
}

void	check_map(t_data *d, t_pars *pars)
{
	d->line = NULL;
	d->id = NULL;
	while (is_empty_line(d->line) && d->ret > 0)
	{
		free(d->line);
		d->ret = get_next_line(d->fd, &d->line);
	}
	if (d->ret < 0)
		error_exit("Problem encountered while reading file!", d, pars, 0);
	parse_map(d, pars);
	if (d->ret < 0)
		error_exit("Problem encountered while reading file!", d, pars, 0);
	is_valid_map(d, pars);
	pars->map[(int)pars->pos_x][(int)pars->pos_y] = '0';
	close(d->fd);
	if (pars->screen_width > 2880)
		pars->screen_width = 2880;
	if (pars->screen_heigth > 1490)
		pars->screen_heigth = 1490;
}

void	parser(int argc, char **argv, t_pars *pars)
{
	t_data	d;

	init_values(&d, pars);
	if (argc < 2 || argc > 3)
		error_exit("Invalid number of arguments!", 0, 0, 0);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			error_exit("3rd argument can only be \"--save\"!", 0, 0, 0);
		else
			pars->save_arg = 1;
	}
	get_fd(argv[1], ".cub", &d);
	parse_elements(&d, pars);
	check_map(&d, pars);
}
