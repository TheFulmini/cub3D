/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:43:10 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 16:51:09 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUBE3D_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "../mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# endif

typedef struct	s_spritepos
{
	double	x; // x position of the sprite
	double	y; // y position of the sprite
}				t_spritepos;

typedef struct	s_sprites
{
	int		nbrspr; // number of sprites
	int		*order;
	double	*distance;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteWidth;
	int		spriteHeight;
	int		drawStartX;
	int		drawStartY;
	int		drawEndX;
	int		drawEndY;
	double	*ZBuffer;
}				t_sprites;

typedef	struct 	s_textures
{
	int		textdir; // directoion NO, SO, EA, WE of the texture
	double	wallX; // value when the wall has been hit : y coordinates if side == 0, x coordinates if side ==1 
	int		texX; // x coordinates of the texture
	int		texY; // y coordinates of the texture
	double	step; // indicates how much we need to add to the coordinates of the textuere for each pixel
	double	textPos; // startring coordinates
}				t_textures;

typedef struct	s_ray
{

}				t_ray;

typedef struct	s_data
{
//get mlx and keys
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		forward;
	int		back;
	int		left;
	int		right;
	int		rotate_l;
	int		rotate_r;
	int		minimapchelle; // ??????????
	int		width; //recup->texture.width : number of pixels for width of texture
	int		height; //recup->texture.height : number of pixels for height of texture
	void	*img2;
	int		*addr2;
}				t_data;

typedef struct  s_recup
{
	int			Rx;
	int			Ry;
	int			i;
	int			F;
	int			C;
	char		*NO;
	char		*SO;
	char		*EA;
	char		*WE;
	char		*S;
	int			nblines;
	int			sizelines;
	char		**map;
	char		start; // starting position 
	int			dx;
	int			dy;
	int			indicator;
	int			indicator1;
	int			save;
	t_data		texture[5];
	t_data		data;
	t_ray		ray;
	t_textures	t;
	t_sprites	s;
	t_spritepos	*sxy;
}				t_recup;

#endif