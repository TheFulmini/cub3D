/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:47:30 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/03 15:11:39 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_mlx *d)
{
	if (keycode == 13)
		d->move_forward = 1;
	if (keycode == 1)
		d->move_backward = 1;
	if (keycode == 0)
		d->move_left = 1;
	if (keycode == 2)
		d->move_right = 1;
	if (keycode == 123)
		d->look_left = 1;
	if (keycode == 124)
		d->look_right = 1;
	if (keycode == 53)
		clean_exit("Game left by ESC", &d->p, d, 0);
	return (0);
}

int	key_release(int keycode, t_mlx *e)
{
	if (keycode == 13)
		e->move_forward = 0;
	if (keycode == 1)
		e->move_backward = 0;
	if (keycode == 0)
		e->move_left = 0;
	if (keycode == 2)
		e->move_right = 0;
	if (keycode == 123)
		e->look_left = 0;
	if (keycode == 124)
		e->look_right = 0;
	return (0);
}

int	click_exit(t_mlx *d)
{
	clean_exit("Game left by clicking", &d->p, d, 0);
	return (0);
}
