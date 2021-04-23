/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:44:38 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/23 15:52:35 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_textures_vars(t_mlx *d, t_raycast *r)
{
	if (r->side = 0)
		r->wallX = d->p.pos_y+ r->perpWallDist * r->raydirection_x;
	else
		r->wallX = d->p.pos_x+ r->perpWallDist * r->raydirection_y;
	r->wallX -= floor((r->wallX)); //define function
	r->text_x = (int)(r->wallX * (double)d->text_width[r->text_num]);
	if (r->side == 0 && r->raydirection_y > 0)
		r->text_x = d->text_width[r->text_num] - r->text_x - 1;
	if (r->side == 1 && r->raydirection_x < 0)
		r->text_x = d->text_width[r->text_num] - r->text_x - 1;
	r->step = 1.0 * d->text_height[r->text_num] / r->line_heigth;
	r->text_pos = (r->draw_start - d->p.screen_heigth / 2
			+ r->line_heigth / 2) * r->step;
}

void	draw_line(t_mlx *d, t_raycast *r, int x)
{
	int y;

	y = 0;
	while (y < r->draw_start)
	{
		put_pixel(&d->img, x, y, d->p.ceil_color); //define function 
		y++;
	}
	y = r->draw_end;
	while (y < d->p.screen_heigth)
	{
		put_pixel(&d->img, x, y, d->p.floor_color);
		y++;
	}
	y = r->draw_start;
	while (y < r->draw_end)
	{
		r->text_y = (int)r->text_pos;
		r->text_pos += r->step;
		get_pixel(&d->text[r->text_num], r->text_x, r->text_y, &r->colour); //define function
		if (r->side == 1)
			r->colour = (r->colour >> 1) & 8355711;		//discover how this works...
		put_pixel(&d->img, x, y, r->colour);
		y++;
	}
}

void	get_sprite(t_mlx *d, t_raycast *r, t_spritevar *s)
{
	int i;

	set_distance(d, s); //define function
	i = 0;
	while (i < d.p.nb_sprites)
	{
		s->sprite_y = d.p.sprite_tab[s->sprite_order[i]].y - d.p.pos_y;
		s->sprite_x = d.p.sprite_tab[s->sprite_order[i]].x - d.p.pos_x;
		set_sprite(d, s); //define this function
		draw_sprites(d, r, s); // define this function
		i++;
	}
}

void	free_sprites_tab(t_spritevar *s)
{
	if (s->sprite_order)
		free(s->sprite_order);
	if (s->sprite_distance)
		free(s->sprite_distance);
	if (s->zbuffer)
		free(s->zbuffer);
}

int	raycasting(t_mlx *d)
{
	t_spritevar	spr_v;
	int			i;
	t_raycast	r; //define struct

	if (init_sprite_tabs(&spr_v, *d) == 0)
		clean_exit("Memory Error. Not able to allocate sufficient memory", 0, 0, &spr_v);
	i = 0;
	while (i < d->p.screen_width)
	{
		set_raycast_vars(d, &r, i);	//deifne function
		set_textures_vars(d, &r);
		draw_line(d, &r, i);
		spr_v.zbuffer[i++] = r.perpWallDist;
	}
	if (d->p.nb_sprites > 0)
		get_sprites(*d, r, &spr_v);	//define function
	d->img1 = d->img;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img1.img, 0, 0);
	get_player_moves(d, &r);	//define function
	free_sprite_tab(&spr_v);	//define function
	if (d->p.save == 1)
		create_bmp(*d);
	if (d->p.save == 1)
		clean_exit("Image file saved to bmp format.", &d->p, d, 0);
	return (0);
}