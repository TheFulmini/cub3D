/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:02:19 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:55:33 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	create_header(t_mlx d, int fd)
{
	int	wr;

	write(fd, "BM", 2);
	wr = 14 + 40 + 4 * d.p.screen_width * d.p.screen_heigth;
	write(fd, &wr, 4);
	wr = 0;
	write(fd, &wr, 4);
	wr = 54;
	write(fd, &wr, 4);
	wr = 40;
	write(fd, &wr, 4);
	write(fd, &d.p.screen_width, 4);
	write(fd, &d.p.screen_heigth, 4);
	wr = 1;
	write(fd, &wr, 2);
	write(fd, &d.img1.bits_per_pixel, 2);
	wr = 0;
	write(fd, &wr, 32);
}

void	create_bmp(t_mlx d)
{
	int	fd;
	int	x;
	int	y;
	int	color;

	y = d.p.screen_heigth;
	fd = open("./screenshot.bmp", O_CREAT | O_RDWR);
	if (fd == -1)
		clean_exit("Couldn't create bmp file", &d.p, &d, 0);
	create_header(d, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < d.p.screen_width)
		{
			pixel_get(&d.img1, x + 2, y, &color);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}
