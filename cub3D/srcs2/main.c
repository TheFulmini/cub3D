/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:41:58 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:55:31 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	clean_exit(char *exit_msg, t_pars *pars, t_mlx *d, t_spritevars *s)
{
	if (s)
	{
		if (s->sprite_order)
			free(s->sprite_order);
		if (s->sprite_distance)
			free(s->sprite_distance);
		if (s->z_buffer)
			free(s->z_buffer);
	}
	free_pars(pars);
	printf("%s\n", exit_msg);
	if (ft_strcmp("Error : couldn't read xpm texture.", exit_msg))
		mlx_destroy(d);
	exit(0);
}

void	get_start_vectors(t_pars *pars)
{
	pars->dir_x = 0;
	pars->dir_y = 0;
	pars->plane_x = 0;
	pars->plane_y = 0;
	if (pars->dir == 'N')
	{
		pars->dir_y = -1;
		pars->plane_x = 0.66;
	}
	if (pars->dir == 'S')
	{
		pars->dir_y = 1;
		pars->plane_x = -0.66;
	}
	if (pars->dir == 'W')
	{
		pars->dir_x = -1;
		pars->plane_y = -0.66;
	}
	if (pars->dir == 'E')
	{
		pars->dir_x = 1;
		pars->plane_y = 0.66;
	}
}

void	init_moves(t_mlx *d)
{
	d->move_up = 0;
	d->move_down = 0;
	d->look_left = 0;
	d->look_right = 0;
	d->move_left = 0;
	d->move_right = 0;
}

void	init_textures(t_mlx *d)
{
	int		i;
	char	*path;

	i = 0;
	while (i < 5)
	{
		if (i == 0)
			path = d->p.w_path;
		if (i == 1)
			path = d->p.e_path;
		if (i == 2)
			path = d->p.s_path;
		if (i == 3)
			path = d->p.n_path;
		if (i == 4)
			path = d->p.sprite_path;
		d->tex[i].img = mlx_xpm_file_to_image(d->mlx, path,
				&d->tex_width[i], &d->tex_heigth[i]);
		if (!d->tex[i].img)
			clean_exit("Error : couldn't read xpm texture.", &d->p, d, 0);
		d->tex[i].addr = mlx_get_data_addr(d->tex[i].img,
				&d->tex[i].bits_per_pixel, &d->tex[i].line_length,
				&d->tex[i].endian);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	d;

	parser(argc, argv, &d.p);
	get_start_vectors(&d.p);
	init_moves(&d);
	init_mlx_vars(&d);
	init_textures(&d);
	mlx_hook(d.win, 2, 1L << 0, key_press, &d);
	mlx_hook(d.win, 3, 1L << 1, key_release, &d);
	mlx_hook(d.win, 17, 1L << 17, red_cross, &d);
	mlx_loop_hook(d.mlx, raycasting, &d);
	mlx_do_key_autorepeatoff(d.mlx);
	mlx_loop(d.mlx);
}
