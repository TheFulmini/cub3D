/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:33:49 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/28 18:28:15 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	sort_sprites(t_sprvar *sprite, int amount)
{
	int		i;
	int		j;
	double	db_temp;
	int		i_temp;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < amount)
		{
			if (sprite->sprite_distance[j] > sprite->sprite_distance[i])
			{
				db_temp = sprite->sprite_distance[i];
				sprite->sprite_distance[i] = sprite->sprite_distance[j];
				sprite->sprite_distance[j] = db_temp;
				i_temp = sprite->sprite_order[i];
				sprite->sprite_order[i] = sprite->sprite_order[j];
				sprite->sprite_order[j] = i_temp;
			}
			j++;
		}
		i++;
	}
}

int	init_sprite_tab(t_sprvar *s, t_mlx d)
{
	int	i;

	i = 1;
	s->zbuffer = malloc(sizeof(double) * d.p.screen_width);
	if (s->zbuffer == NULL)
		i = 0;
	s->sprite_order = malloc(sizeof(int) * d.p.nb_sprites);
	if (s->sprite_order == NULL)
		i = 0;
	s->sprite_distance = malloc(sizeof(double) * d.p.nb_sprites);
	if (s->sprite_distance == NULL)
		i = 0;
	return (i);
}

void	set_distance(t_mlx d, t_sprvar *s)
{
	int	i;

	i = 0;
	while (i < d.p.nb_sprites)
	{
		s->sprite_order[i] = i;
		s->sprite_distance[i] = ((d.p.pos_y - d.p.sprite_tab[i].y)
				* (d.p.pos_y - d.p.sprite_tab[i].y)
				+ (d.p.pos_x - d.p.sprite_tab[i].x)
				* (d.p.pos_x - d.p.sprite_tab[i].x));
		i++;
	}
	sort_sprites(s, d.p.nb_sprites);
}

void	set_sprite(t_mlx d, t_sprvar *s)
{
	s->inv_det = 1.0 / (d.p.plane_x * d.p.dir_y - d.p.dir_x * d.p.plane_y);
	s->transform_x = s->inv_det * (d.p.dir_y
			* s->sprite_y + d.p.dir_x * s->sprite_x);
	s->transform_y = s->inv_det * (d.p.plane_y
			* s->sprite_y + d.p.plane_x * s->sprite_x);
	s->sprite_screen_x = (int)((d.p.screen_width / 2)
			* (1 + s->transform_x / s->transform_y));
	s->sprite_height = abs((int)(d.p.screen_height / (s->transform_y)));
	s->draw_start_y = -s->sprite_height / 2 + d.p.screen_height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + d.p.screen_height / 2;
	if (s->draw_end_y >= d.p.screen_height)
		s->draw_end_y = d.p.screen_height - 1;
	s->sprite_width = abs((int)(d.p.screen_height / (s->transform_y)));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_y = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= d.p.screen_width)
		s->draw_end_x = d.p.screen_width - 1;
}

void	draw_sprite(t_mlx d, t_raycast r, t_sprvar *s)
{
	int	y;

	s->stripe = s->draw_start_x;
	while (s->stripe < s->draw_end_x)
	{
		r.text_x = (int)(256 * (s->stripe
					- (-s->sprite_width / 2 + s->sprite_screen_x))
				* d.text_width[4] / s->sprite_width) / 256;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < d.p.screen_width
			&& s->transform_y < s->zbuffer[s->stripe])
		{
			y = s->draw_start_y;
			while (y < s->draw_end_y)
			{
				r.text_y = (((y * 256 - d.p.screen_height
								* 128 + s->sprite_height * 128)
							* d.text_height[4]) / s->sprite_height) / 256;
				get_pixel(&d.text[4], r.text_x, r.text_y, &r.colour);
				if ((r.colour & 0x00FFFFFF) != 0)
					put_pixel(&d.img1, s->stripe, y, r.colour);
				y++;
			}
		}
		s->stripe++;
	}
}
