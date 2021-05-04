/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:34:57 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/04 13:37:23 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mlx_destroy(t_mlx *d)
{
	int	i;

	i = 0;
	mlx_destroy_image(d->mlx_ptr, d->img.img);
	while (i < 5)
	{
		mlx_destroy_image(d->mlx_ptr, d->text[i].img);
		i++;
	}
	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
}

void	put_pixel(t_img *img, int x, int y, int colour)
{
	char	*dest;
	int		offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dest = img->address + offset;
	*(unsigned int *)dest = colour;
}

void	get_pixel(t_img *img, int x, int y, int *colour)
{
	char	*dest;
	int		offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dest = img->address + offset;
	*colour = *(int *)dest;
}

void	init_mlx_var(t_mlx *d)
{
	d->mlx_ptr = mlx_init();
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->p.screen_width,
			d->p.screen_height, "Cub3D");
	d->img.img = mlx_new_image(d->mlx_ptr, d->p.screen_width, d->p.screen_height);
	d->img.address = mlx_get_data_addr(d->img.img, &d->img.bits_per_pixel,
			&d->img.line_length, &d->img.endian);
	d->img1.img = mlx_new_image(d->mlx_ptr, d->p.screen_width,
			d->p.screen_height);
	d->img1.address = mlx_get_data_addr(d->img1.img, &d->img1.bits_per_pixel,
			&d->img1.line_length, &d->img1.endian);
}
