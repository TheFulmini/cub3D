/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amilis <amilis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:44:43 by amilis            #+#    #+#             */
/*   Updated: 2021/04/20 12:55:28 by amilis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_mlx *d)
{
	if (keycode == 13)
		d->move_up = 1;
	if (keycode == 1)
		d->move_down = 1;
	if (keycode == 123)
		d->look_left = 1;
	if (keycode == 124)
		d->look_right = 1;
	if (keycode == 0)
		d->move_left = 1;
	if (keycode == 2)
		d->move_right = 1;
	if (keycode == 53)
		clean_exit("ESC key pressed. Exiting.", &d->p, d, 0);
	return (0);
}

int	key_release(int keycode, t_mlx *inst)
{
	if (keycode == 13)
		inst->move_up = 0;
	if (keycode == 1)
		inst->move_down = 0;
	if (keycode == 123)
		inst->look_left = 0;
	if (keycode == 124)
		inst->look_right = 0;
	if (keycode == 0)
		inst->move_left = 0;
	if (keycode == 2)
		inst->move_right = 0;
	return (0);
}

int	red_cross(t_mlx *d)
{
	clean_exit("Red cross clicked. Exiting.", &d->p, d, 0);
	return (0);
}
