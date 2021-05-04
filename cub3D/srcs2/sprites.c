/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:36:13 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:32 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	sort_sprites(t_spritevars *spr, int amount)
{
	int		i;
	int		j;
	double	db_tmp;
	int		i_tmp;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < amount)
		{
			if (spr->sprite_distance[j] > spr->sprite_distance[i])
			{
				db_tmp = spr->sprite_distance[i];
				spr->sprite_distance[i] = spr->sprite_distance[j];
				spr->sprite_distance[j] = db_tmp;
				i_tmp = spr->sprite_order[i];
				spr->sprite_order[i] = spr->sprite_order[j];
				spr->sprite_order[j] = i_tmp;
			}
			j++;
		}
		i++;
	}
}

int	init_sprite_tabs(t_spritevars *s, t_mlx d)
{
	int	i;

	i = 1;
	s->z_buffer = malloc(sizeof(double) * d.p.screen_width);
	if (s->z_buffer == NULL)
		i = 0;
	s->sprite_order = malloc(sizeof(int) * d.p.nb_of_sprites);
	if (s->sprite_order == NULL)
		i = 0;
	s->sprite_distance = malloc(sizeof(double) * d.p.nb_of_sprites);
	if (s->sprite_distance == NULL)
		i = 0;
	return (i);
}

void	set_distance_values(t_mlx d, t_spritevars *s)
{
	int	i;

	i = 0;
	while (i < d.p.nb_of_sprites)
	{
		s->sprite_order[i] = i;
		s->sprite_distance[i] = ((d.p.pos_y - d.p.sprite_tab[i].y)
				* (d.p.pos_y - d.p.sprite_tab[i].y)
				+ (d.p.pos_x - d.p.sprite_tab[i].x)
				* (d.p.pos_x - d.p.sprite_tab[i].x));
		i++;
	}
	sort_sprites(s, d.p.nb_of_sprites);
}

void	set_sprite_values(t_mlx d, t_spritevars *s)
{
	s->inv_det = 1.0 / (d.p.plane_x * d.p.dir_y - d.p.dir_x * d.p.plane_y);
	s->transform_x = s->inv_det
		* (d.p.dir_y * s->sprite_y - d.p.dir_x * s->sprite_x);
	s->transform_y = s->inv_det
		* (-d.p.plane_y * s->sprite_y + d.p.plane_x * s->sprite_x);
	s->sprite_screen_x = (int)((d.p.screen_width / 2)
			* (1 + s->transform_x / s->transform_y));
	s->sprite_heigth = abs((int)(d.p.screen_heigth / (s->transform_y)));
	s->draw_start_y = -s->sprite_heigth / 2 + d.p.screen_heigth / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_heigth / 2 + d.p.screen_heigth / 2;
	if (s->draw_end_y >= d.p.screen_heigth)
		s->draw_end_y = d.p.screen_heigth - 1;
	s->sprite_width = abs((int)(d.p.screen_heigth / (s->transform_y)));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= d.p.screen_width)
		s->draw_end_x = d.p.screen_width - 1;
}

void	draw_sprites(t_mlx d, t_rayc r, t_spritevars *s)
{
	int	y;

	s->stripe = s->draw_start_x;
	while (s->stripe < s->draw_end_x)
	{
		r.tex_x = (int)(256 * (s->stripe
					- (-s->sprite_width / 2 + s->sprite_screen_x))
				* d.tex_width[4] / s->sprite_width) / 256;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < d.p.screen_width
			&& s->transform_y < s->z_buffer[s->stripe])
		{
			y = s->draw_start_y;
			while (y < s->draw_end_y)
			{
				r.tex_y = (((y * 256 - d.p.screen_heigth
								* 128 + s->sprite_heigth * 128)
							* d.tex_heigth[4]) / s->sprite_heigth) / 256;
				pixel_get(&d.tex[4], r.tex_x, r.tex_y, &r.color);
				if ((r.color & 0x00FFFFFF) != 0)
					pixel_put(&d.img1, s->stripe, y, r.color);
				y++;
			}
		}
		s->stripe++;
	}	
}
