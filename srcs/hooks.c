/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:47:30 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/14 14:19:39 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_mlx *d)
{
	if (keycode == KEY_W_Z || keycode == KEY_UP)
		d->move_forward = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		d->move_backward = 1;
	if (keycode == KEY_A_Q)
		d->move_left = 1;
	if (keycode == KEY_D)
		d->move_right = 1;
	if (keycode == KEY_LEFT || keycode == KEY_Q_A)
		d->look_left = 1;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		d->look_right = 1;
	if (keycode == ESC)
		clean_exit("Game left by ESC", &d->p, d, 0);
	if (keycode == SAVE_X)
		save_bmp(*d);
	return (0);
}

int	key_release(int keycode, t_mlx *e)
{
	if (keycode == KEY_W_Z || keycode == KEY_UP)
		e->move_forward = 0;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		e->move_backward = 0;
	if (keycode == KEY_A_Q)
		e->move_left = 0;
	if (keycode == KEY_D)
		e->move_right = 0;
	if (keycode == KEY_LEFT || keycode == KEY_Q_A)
		e->look_left = 0;
	if (keycode == KEY_RIGHT || keycode == KEY_E)
		e->look_right = 0;
	return (0);
}

int	click_exit(t_mlx *d)
{
	clean_exit("Game left by clicking", &d->p, d, 0);
	return (0);
}
