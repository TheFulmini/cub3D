/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:33:49 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/27 16:00:53 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	sort_sprites(t_spritevar *sprite, int amount)
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

int		init_sprite_tab(t_spritevar *spr, t_mlx d)
{
	int	i;

	i = 1;
	spr->zbuffer = malloc(sizeof(double) * d.p.screen_width);
	if (spr->zbuffer == NULL)
		i = 0;
	spr->sprite_order = malloc(sizeof(int) * d.p.nb_sprites);
	if (spr->sprite_order == NULL)
		i = 0;
	spr->sprite_distance = malloc(sizeof(double) * d.p.nb_sprites);
	if (spr->sprite_distance == NULL)
		i = 0;
	return (i);
}

void	set_distance(t_mlx d, t_spritevar *spr)
{
	int	i;

	i = 0;
	while (i < d.p.nb_sprites)
	{
		spr->sprite_order[i] = i;
		spr->sprite_distance[i] = ((d.p.pos_y - d.p.sprite_tab[i].y)
					* (d.p.pos_y - d.p.sprite_tab[i].y)
					+ (d.p.pos_x - d.p.sprite_tab[i].x)
					* (d.p.pos_x - d.p.sprite_tab[i].x));
		i++;
	}
	sort_sprites(spr, d.p.nb_sprites);
}

void	set_sprite(t_mlx d, t_spritevar *spr)
{
	spr->inv_det = 1.0 / (d.p.plane_x * d.p.dir_y - d.p.dir_x * d.p.plane_y);
	spr->transform_x = spr->inv_det * (d.p.dir_y
			* spr->sprite_y = d.p.dir_x * spr->sprite_x);
	spr->transform_y = spr->inv_det * (d.p.plane_y
			* spr->sprite_y + d.p.plane_x * spr->sprite_x);
	spr->sprite_height = abs((int)(d.p.screen_width / 2)
			* (1 + spr->transform_x / spr->transform_y));
	spr->sprite_height = abs((int)(d.p.screen_height / (s->transform_y)));
	spr->draw_start_y = -spr->sprite_height / 2 + d.p.screen_heigth / 2;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	spr->draw_end_y = spr->sprite_height / 2 + d.p.screen_heigth / 2;
	if (spr->draw_end_y >= d.p.screen_heigth)
		spr->draw_end_y = d.p.screen_heigth - 1;
	spr->sprite_width = abs((int)(d.p.screen_heigth / (spr->transform_y)));
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_y = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_end_x >= d.p.screen_width)
		spr->draw_end_x = d.p.screen_width - 1;
}

void	draw_sprite(t_mlx d, t_raycast r, t_spritevar *spr)
{
	int y;

	spr->stripe = spr->draw_start_x;
	while (spr->stripe < spr->draw_end_x)
	{
		r.text_x = (int)(256 * (spr->stripe
					- (-spr->sprite_width / 2 + spr->sprite_screen_x))
					* d.text_width[4] / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && spr->stripe > 0 && spr->stripe < d.p.screen_width
			&& spr->transform_y < spr->zbuffer[spr->stripe])
		{
			y = spr->draw_start_y;
			while (y < spr->draw_end_y)
			{
				r.text_y = (((y * 256 - d.p.screen_heigth
							* 128 + spr->sprite_height * 128)
							* d.text_height[4] / spr->sprite_height / 256;
				get_pixel(&d.text[4], r.text_x, r.text_y, &r.colour);
				if ((r.colour & 0x00FFFFFF) != 0)
					put_pixel(&d.img, spr->stripe, y, r.colour);
				y++;
			}
		}
		spr->stripe++;
	}
}
