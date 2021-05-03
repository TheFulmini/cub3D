/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:39:16 by amilis            #+#    #+#             */
/*   Updated: 2021/05/03 11:57:40 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_updown(t_mlx *d, t_rayc *r)
{
	if (d->move_up == 1)
	{
		if (d->p.map[(int)(d->p.pos_x + d->p.dir_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x += d->p.dir_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
			+ d->p.dir_x * r->move_speed)] == '0')
			d->p.pos_y += d->p.dir_x * r->move_speed;
	}
	if (d->move_down == 1)
	{
		if (d->p.map[(int)(d->p.pos_x - d->p.dir_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x -= d->p.dir_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
			- d->p.dir_x * r->move_speed)] == '0')
			d->p.pos_y -= d->p.dir_x * r->move_speed;
	}
}

void	move_leftright(t_mlx *d, t_rayc *r)
{
	if (d->move_left == 1)
	{	
		if (d->p.map[(int)(d->p.pos_x - d->p.plane_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x -= d->p.plane_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
			- d->p.plane_x * r->move_speed)] == '0')
			d->p.pos_y -= d->p.plane_x * r->move_speed;
	}
	if (d->move_right == 1)
	{
		if (d->p.map[(int)(d->p.pos_x + d->p.plane_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x += d->p.plane_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
			+ d->p.plane_x * r->move_speed)] == '0')
			d->p.pos_y += d->p.plane_x * r->move_speed;
	}
}

void	turn_leftright(t_mlx *d, t_rayc *r)
{
	r->old_dir_x = d->p.dir_y;
	r->old_plane_x = d->p.plane_y;
	if (d->look_right == 1)
	{
		d->p.dir_y = d->p.dir_y * cos(-r->turn_speed)
			- d->p.dir_x * sin(-r->turn_speed);
		d->p.dir_x = r->old_dir_x * sin(-r->turn_speed)
			+ d->p.dir_x * cos(-r->turn_speed);
		d->p.plane_y = d->p.plane_y * cos(-r->turn_speed)
			- d->p.plane_x * sin(-r->turn_speed);
		d->p.plane_x = r->old_plane_x * sin(-r->turn_speed)
			+ d->p.plane_x * cos(-r->turn_speed);
	}
	if (d->look_left == 1)
	{
		d->p.dir_y = d->p.dir_y * cos(r->turn_speed)
			- d->p.dir_x * sin(r->turn_speed);
		d->p.dir_x = r->old_dir_x * sin(r->turn_speed)
			+ d->p.dir_x * cos(r->turn_speed);
		d->p.plane_y = d->p.plane_y * cos(r->turn_speed)
			- d->p.plane_x * sin(r->turn_speed);
		d->p.plane_x = r->old_plane_x * sin(r->turn_speed)
			+ d->p.plane_x * cos(r->turn_speed);
	}
}

void	get_player_moves(t_mlx *d, t_rayc *r)
{
	r->move_speed = 0.2;
	r->turn_speed = 0.08;
	move_updown(d, r);
	move_leftright(d, r);
	turn_leftright(d, r);
}
