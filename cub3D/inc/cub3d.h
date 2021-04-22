/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:19:59 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 18:17:23 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 43

typedef	struct 	s_sprites
{
	double	x;
	double	y;
}				t_sprites;

typedef	struct	s_spritevar
{
	int		*sprite_order;
	double	*sprite_distance;
	double	*zbuffer;
	double	sprite_y;
	double	sprite_x;
	double	inv_det;
	double	transform_y;
	double	transform_x;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	int		stripe;
}				t_spritevar;


typedef	struct	s_img
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_elems
{
	int	res;
	int	no_text;
	int	so_text;
	int	ea_text;
	int	we_text;
	int	spr_text;
	int	ceiling_col;
	int	floor_col;
}				t_elems;

typedef	struct	s_parse
{
	int			screen_width;
	int			screen_heigth;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*sprite_path;
	int			floor_color;
	int			ceil_color;
	char		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		**map;
	int			nb_sprites;
	int			save_arg;
	t_sprites	*sprite_tab;
}				t_parse;

typedef	struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		look_left;
	int		look_right;
	int		tex_width[5];
	int		text_height[5];
	t_img	img;
	t_img	img1;
	t_img	text[5];
	t_parse	p;
}				t_mlx;


typedef struct	s_data
{
	char	*line;
	char	*id;
	int		fd;
	int		ret;
}				t_data;


// GNL functions
unsigned long	ft_strlen(char *str);
char			*truncate_str_free(char *str);
void			stock_supp(const char *str, char *supp, int nb_char, int mode);
char			*ft_strjoin_free(char *str, char *buffer, int nb_char);
int				newline_in_Str(char *str, int nb_char, int mode);
int				end_or_error(int ret, char *buffer, char **sup_str, char *line);
int				malloc_str(char **buffer, char **supp, int fd);
char			*ft_strdup(const char *str);
int				make_line(int fd, char *buffer, char **line, char **supp);
int				get_next_line(int fd, char **line);

// parsing.c
void	free_parser(t_parse *pars);
void	error_exit(char *error_msg, t_data *d, t_parse *pars, char **map);
void	check_map(t_data *d, t_parse *pars);
void	parsing(int argc, char **argv, t_parse *pars);



#endif