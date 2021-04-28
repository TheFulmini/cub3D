/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:04:52 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:26 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_algo(t_rayc *r, t_mlx *d)
{
	while (1)
	{
		if (r->sidedist_y < r->sidedist_x)
		{
			r->sidedist_y += r->deltadist_y;
			r->map_x += r->step_y;
			r->side = 0;
		}
		else
		{
			r->sidedist_x += r->deltadist_x;
			r->map_y += r->step_x;
			r->side = 1;
		}
		if (d->p.map[r->map_x][r->map_y] == '1')
			break ;
	}
	if (r->side == 0)
		r->perpwdist = (r->map_x - d->p.pos_x
				+ (1 - r->step_y) / 2) / r->raydir_y;
	else
		r->perpwdist = (r->map_y - d->p.pos_y
				+ (1 - r->step_x) / 2) / r->raydir_x;
}

void	set_ray_dir_len(t_rayc *r, t_mlx *d)
{
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (d->p.pos_x - r->map_x) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_x + 1.0 - d->p.pos_x) * r->deltadist_y;
	}
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (d->p.pos_y - r->map_y) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_y + 1.0 - d->p.pos_y) * r->deltadist_x;
	}
}

void	set_raycasting_vars(t_mlx *d, t_rayc *r, int x)
{
	r->raydir_x = d->p.dir_x + d->p.plane_x
		* (2 * x / (double)(d->p.screen_width - 1) - 1);
	r->raydir_y = d->p.dir_y + d->p.plane_y
		* (2 * x / (double)(d->p.screen_width - 1) - 1);
	r->map_x = (int)d->p.pos_x;
	r->map_y = (int)d->p.pos_y;
	r->deltadist_y = fabs(1 / r->raydir_y);
	r->deltadist_x = fabs(1 / r->raydir_x);
	set_ray_dir_len(r, d);
	dda_algo(r, d);
	r->line_heigth = (int)(d->p.screen_heigth / r->perpwdist);
	r->draw_start = -r->line_heigth / 2 + d->p.screen_heigth / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_heigth / 2 + d->p.screen_heigth / 2;
	if (r->draw_end >= d->p.screen_heigth || r->draw_end < 0)
		r->draw_end = d->p.screen_heigth - 1;
	if (r->side == 1 && r->raydir_x > 0)
		r->tex_num = 0;
	if (r->side == 1 && r->raydir_x <= 0)
		r->tex_num = 1;
	if (r->side == 0 && r->raydir_y > 0)
		r->tex_num = 2;
	if (r->side == 0 && r->raydir_y <= 0)
		r->tex_num = 3;
}
