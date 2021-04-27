/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:17:12 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/27 16:31:23 by afulmini         ###   ########.fr       */
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
	write(fd, &d.img.bits_per_pixel, 2);
	wr = 0;
	write(fd, &wr, 32);
}

void	save_bmp(t_mlx d)
{
	int	fd;
	int	x;
	int	y;
	int	colour;

	y = d.p.screen_heigth;
	fd = open("./saved_image.bmp", O_CREAT | O_RDWR);
	if (fd == -1)
		clean_exit("Impossible to save the bmp file.", &d.p, &d, 0);
	create_header(d, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < d.p.screen_width)
		{
			get_pixel(&d.img, x + 2, y, &colour);
			write(fd, &colour, 4);
			x++;
		}
		y--;
	}
}
