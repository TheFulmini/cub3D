/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:42:04 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:55:36 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mlx_destroy(t_mlx *d)
{
	int	i;

	i = 0;
	mlx_destroy_image(d->mlx, d->img1.img);
	while (i < 5)
	{
		mlx_destroy_image(d->mlx, d->tex[i].img);
		i++;
	}
	mlx_destroy_window(d->mlx, d->win);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	pixel_get(t_img *img, int x, int y, int *color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*color = *(int *)dst;
}

void	init_mlx_vars(t_mlx *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->p.screen_width,
			d->p.screen_heigth, "cub3D");
	d->img1.img = mlx_new_image(d->mlx, d->p.screen_width, d->p.screen_heigth);
	d->img1.addr = mlx_get_data_addr(d->img1.img, &d->img1.bits_per_pixel,
			&d->img1.line_length, &d->img1.endian);
	d->img2.img = mlx_new_image(d->mlx, d->p.screen_width, d->p.screen_heigth);
	d->img2.addr = mlx_get_data_addr(d->img2.img, &d->img2.bits_per_pixel,
			&d->img2.line_length, &d->img2.endian);
}
