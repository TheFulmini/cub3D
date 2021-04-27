/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:56:22 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/27 15:20:50 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_algorithm(t_raycast *r, t_mlx *d)
{
	while (1)
	{
		if (r->side_dist_y < r->side_dist_x)
		{
			r->side_dist_y += r->deltadist_y;
			r->map_x += r->step_y;
			r->side = 0;
		}
		else
		{
			r->side_dist_x += r->deltadist_x;
			r->map_y += r->step_x;
			r->side = 1;
		}
		if (d->p.map[r->map_x][r->map_y] == '1')
			break ;
	}
	if (r->side == 0)
		r->perpWallDist = (r->map_x - d->p.pos_x
				+ (1 - r->step_y) / 2) / r->raydir_y;
	else
		r->perpWallDist = (r->map_y - d->p.pos_y
				+ (1 - r->step_x) / 2) / r->raydir_x;
}

void	set_ray_direction_length(t_raycast *r, t_mlx *d)
{
	if (r->raydirection_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (d->p.pos_x - r->map_x) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_x + 1.0 - d->p.pos_x) * r->deltadist_y;
	}
	if (r->raydirection_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (d->p.pos_y - r->map_y) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_y + 1.0 - d->p.pos_y) * r->deltadist_x;
	}
}

void	set_raycast_var(t_mlx *d, t_raycast *r, int x)
{
	r->raydirection_x = d->p.dir_x + d->p.plane_x
		* (2 * x / (double)(d->p.screen_width - 1) - 1);
	r->raydirection_y = d->p.dir_y + d->p.plane_y
		* (2 * x / (double)(d->p.screen_width - 1) - 1);
	r->map_x = (int)d->p.pos_x;
	r->map_y = (int)d->p.pos_y;
	r->deltadist_x = fabs(1 / r->raydirection_y);
	r->deltadist_x = fabs(1 / r->raydirection_x);
	set_ray_direction_length(r, d);
	dda_algorithm(r, d);
	r->line_heigth = (int)(d->p.screen_heigth / r->perpWallDist);
	r->draw_start = -r->line_heigth / 2 + d->p.screen_heigth / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_heigth / 2 + d->p.screen_heigth / 2;
	if (r->draw_end >= d->p.screen_heigth)
		r->draw_end = d->p.screen_heigth - 1;
	if (r->side == 1 && r->raydirection_x > 0)
		r->text_num = 0;
	if (r->side == 1 && r->raydirection_x <= 0)
		r->text_num = 1;
	if (r->side == 0 && r->raydirection_y > 0)
		r->text_num = 2;
	if (r->side == 0 && r->raydirection_y <= 0)
		r->text_num = 3;
}
