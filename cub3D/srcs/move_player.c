/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:08:13 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/27 12:47:05 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward_backward(t_mlx *d, t_raycast *r)
{
	if (d->move_forward == 1)
	{
		if (d->p.map[(int)(d->p.pos_x + d->p.dir_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x += d->p.dir_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_y][(int)(d->p.pos_y
				+ d->p.dir_x * r->move_speed)] == '0')
			d->p.pos_y += d->p.dir_x * r->move_speed;
	}
	if (d->move_backward == 1)
	{
		if (d->p.map[(int)(d->p.pos_x - d->p.dir_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x -= d->p.dir_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
				- d->p.dir_x * r->move_speed)] == '0')
			d->p.pos_y -= d->p.dir_x * r->move_speed;
	}
}

void	move_left_rigth(t_mlx *d, t_raycast *r)
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
		if (d->p.map[(int)(d->p.pos_x - d->p.plane_y
				* r->move_speed)][(int)d->p.pos_y] == '0')
			d->p.pos_x += d->p.plane_y * r->move_speed;
		if (d->p.map[(int)d->p.pos_x][(int)(d->p.pos_y
				+ d->p.plane_x * r->move_speed)] == '0')
			d->p.pos_y += d->p.plane_x * r->move_speed;
	}
}

void	turn_left_rigth(t_mlx *d, t_raycast *r)
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

void	get_player_moves(t_mlx *d, t_raycast *r)
{
	r->move_speed = 0.5;
	r->turn_speed = 0.1;
	move_forward_backward(d, r);
	move_left_rigth(d, r);
	turn_left_rigth(d, r);
}