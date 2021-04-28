/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:58:16 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:30 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_texturing_vars(t_mlx *d, t_rayc *r)
{
	if (r->side == 0)
		r->wall_x = d->p.pos_y + r->perpwdist * r->raydir_x;
	else
		r->wall_x = d->p.pos_x + r->perpwdist * r->raydir_y;
	r->wall_x -= floor((r->wall_x));
	r->tex_x = (int)(r->wall_x * (double)d->tex_width[r->tex_num]);
	if (r->side == 0 && r->raydir_y > 0)
		r->tex_x = d->tex_width[r->tex_num] - r->tex_x - 1;
	if (r->side == 1 && r->raydir_x < 0)
		r->tex_x = d->tex_width[r->tex_num] - r->tex_x - 1;
	r->step = 1.0 * d->tex_heigth[r->tex_num] / r->line_heigth;
	r->tex_pos = (r->draw_start - d->p.screen_heigth / 2
			+ r->line_heigth / 2) * r->step;
}

void	draw_line(t_mlx *d, t_rayc *r, int x)
{
	int	y;

	y = 0;
	while (y < r->draw_start)
	{
		pixel_put(&d->img1, x, y, d->p.ceiling_color);
		y++;
	}
	y = r->draw_end;
	while (y < d->p.screen_heigth)
	{
		pixel_put(&d->img1, x, y, d->p.floor_color);
		y++;
	}
	y = r->draw_start;
	while (y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos;
		r->tex_pos += r->step;
		pixel_get(&d->tex[r->tex_num], r->tex_x, r->tex_y, &r->color);
		if (r->side == 1)
			r->color = (r->color >> 1) & 8355711;
		pixel_put(&d->img1, x, y, r->color);
		y++;
	}
}

void	get_sprites(t_mlx d, t_rayc r, t_spritevars *s)
{
	int	i;

	set_distance_values(d, s);
	i = 0;
	while (i < d.p.nb_of_sprites)
	{
		s->sprite_y = d.p.sprite_tab[s->sprite_order[i]].y - d.p.pos_y;
		s->sprite_x = d.p.sprite_tab[s->sprite_order[i]].x - d.p.pos_x;
		set_sprite_values(d, s);
		draw_sprites(d, r, s);
		i++;
	}
}

void	free_spr_tabs(t_spritevars *s)
{
	if (s->sprite_order)
		free(s->sprite_order);
	if (s->sprite_distance)
		free(s->sprite_distance);
	if (s->z_buffer)
		free(s->z_buffer);
}

int	raycasting(t_mlx *d)
{
	t_rayc			r;
	int				x;
	t_spritevars	spr_v;

	if (init_sprite_tabs(&spr_v, *d) == 0)
		clean_exit("Memory allocation error.", 0, 0, &spr_v);
	x = 0;
	while (x < d->p.screen_width)
	{
		set_raycasting_vars(d, &r, x);
		set_texturing_vars(d, &r);
		draw_line(d, &r, x);
		spr_v.z_buffer[x++] = r.perpwdist;
	}
	if (d->p.nb_of_sprites > 0)
		get_sprites(*d, r, &spr_v);
	d->img2 = d->img1;
	mlx_put_image_to_window(d->mlx, d->win, d->img2.img, 0, 0);
	get_player_moves(d, &r);
	free_spr_tabs(&spr_v);
	if (d->p.save_arg == 1)
		create_bmp(*d);
	if (d->p.save_arg == 1)
		clean_exit("BMP file saved.", &d->p, d, 0);
	return (0);
}
