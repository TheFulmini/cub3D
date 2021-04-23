/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:05:29 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/23 14:54:57 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	clean_exit(char *exit_msg, t_parse *pars, t_mlx *d, t_spritevar *s)
{
	if (s)
	{
		if (s->sprite_order)
			free(s->sprite_order);
		if (s->sprite_distance)
			free(s->sprite_distance);
		if (s->zbuffer)
			free(s->zbuffer);
	}
	free_parser(pars);
	printf("%s\n", exit_msg);
	if (ft_strncmp("Error : couldn't read xpm texture.", exit_msg))
		mlx_destroy(d); //define function
	exit(0);
}

void	get_start_vectors(t_parse *pars)
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
	if (pars->dir == 'N')
	{
		pars->dir_y = -1;
		pars->plane_x = 0.66;
	}
	if (pars->dir == 'N')
	{
		pars->dir_y = -1;
		pars->plane_x = 0.66;
	}


}

void	init_moves(t_mlx *d)
{
	d->move_up = 0;
	d->move_down = 0;
	d->move_left = 0;
	d->move_right = 0;
	d->look_left = 0;
	d->look_right = 0;
}

void	init_textures(t_mlx *d)
{
	int 	i;
	char	*path;

	i = 0;
	while (i < 5)
	{
		if (i == 0)
			path = d->p.we_path;
		if (i == 1)
			path = d->p.ea_path;
		if (i == 2)
			path = d->p.so_path;
		if (i == 3)
			path = d->p.no_path;
		if (i == 4)
			path = d->p.sprite_path;
		if (!(d->text[i].img = mlx_xpm_file_to_image(d->mlx_ptr, path,
				&d->text_width[i], &d->text_height[i])))
			clean_exit("Error: could not read texture file.", &d->p, d, 0);
		d->text[i].address = mlx_get_data_addr(d->text[i].img,
				&d->text[i].bits_per_pixel, &d->text[i].line_length,
				&d->text[i].endian);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	d;

	parser(argc, argv, &d.p);
	get_start_vectors(&d.p);
	init_moves(&d);
	init_mlx_var(&d); // define function
	init_textures(&d);
	mlx_hook(d.win_ptr, 2, 1L << 0, key_press, &d);	// define these functions
	mlx_hook(d.win_ptr, 3, 1L << 1, key_release, &d); //define these functions
	mlx_hook(d.win_ptr, 17, 1L << 17, click_exit, &d); //define these functions
	mlx_loop_hook(d.mlx_ptr, raycasting, &d); //define thois function
	mlx_do_key_autorepeatoff(d.mlx_ptr); //define function
	mlx_loop(d.mlx_ptr);
}