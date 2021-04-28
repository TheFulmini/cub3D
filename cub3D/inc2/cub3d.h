/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:58:04 by amilis            #+#    #+#             */
/*   Updated: 2021/04/28 19:21:39 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 32

typedef struct s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef struct s_spritevars
{
	int		*sprite_order;
	double	*sprite_distance;
	double	*z_buffer;
	double	sprite_y;
	double	sprite_x;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_heigth;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
}				t_spritevars;

typedef struct s_rayc
{
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_y;
	double	deltadist_x;
	double	perpwdist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_heigth;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	double	move_speed;
	double	turn_speed;
	double	old_dir_x;
	double	old_plane_x;
	int		color;
}				t_rayc;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_pars
{
	int			screen_width;
	int			screen_heigth;
	char		*n_path;
	char		*s_path;
	char		*w_path;
	char		*e_path;
	char		*sprite_path;
	int			floor_color;
	int			ceiling_color;
	char		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		**map;
	t_sprite	*sprite_tab;
	int			nb_of_sprites;
	int			save_arg;
}				t_pars;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img1;
	t_img	img2;
	int		move_up;
	int		move_down;
	int		look_left;
	int		look_right;
	int		move_left;
	int		move_right;
	t_img	tex[5];
	t_pars	p;
	int		tex_width[5];
	int		tex_heigth[5];
}				t_mlx;

typedef struct s_elems
{
	int	res;
	int	no_text;
	int	so_text;
	int	we_text;
	int	ea_text;
	int	spr_text;
	int	floor_col;
	int	ceiling_col;
}				t_elems;

typedef struct s_data
{
	char	*line;
	char	*id;
	int		fd;
	int		ret;
}				t_data;

// main.c
int				clean_exit(char *exit_msg, t_pars *pars,
					t_mlx *d, t_spritevars *s);
void			get_start_vectors(t_pars *pars);
void			init_moves(t_mlx *d);
void			init_textures(t_mlx *d);
int				main(int argc, char **argv);

// mlx_utils.c
void			mlx_destroy(t_mlx *d);
void			pixel_put(t_img *img, int x, int y, int color);
void			pixel_get(t_img *img, int x, int y, int *color);
void			init_mlx_vars(t_mlx *d);

// hooks.c
int				key_press(int keycode, t_mlx *d);
int				key_release(int keycode, t_mlx *inst);
int				red_cross(t_mlx *d);

// raycasting.c
void			set_texturing_vars(t_mlx *d, t_rayc *r);
void			draw_line(t_mlx *d, t_rayc *r, int x);
void			get_sprites(t_mlx d, t_rayc r, t_spritevars *s);
void			free_spr_tabs(t_spritevars *s);
int				raycasting(t_mlx *inst);

// sprites.c
void			sort_sprites(t_spritevars *spr, int amount);
int				init_sprite_tabs(t_spritevars *s, t_mlx d);
void			set_distance_values(t_mlx d, t_spritevars *s);
void			set_sprite_values(t_mlx d, t_spritevars *s);
void			draw_sprites(t_mlx d, t_rayc r, t_spritevars *s);

// rayc_vectors.c
void			dda_algo(t_rayc *r, t_mlx *d);
void			set_ray_dir_len(t_rayc *r, t_mlx *d);
void			set_raycasting_vars(t_mlx *d, t_rayc *r, int x);

// make_bmp.c
void			create_header(t_mlx d, int fd);
void			create_bmp(t_mlx d);

// player_moves.c
void			move_updown(t_mlx *d, t_rayc *r);
void			move_leftright(t_mlx *d, t_rayc *r);
void			turn_leftright(t_mlx *d, t_rayc *r);
void			get_player_moves(t_mlx *d, t_rayc *r);

// GNL functions
int				end_or_error(int ret, char *buf, char **sup_str, char *line);
int				alloc_strs(char **buf, char **sup, int fd);
char			*ft_strdup(const char *str);
int				make_line(int fd, char *buf, char **line, char **sup);
int				get_next_line(int fd, char **line);
unsigned long	ft_strlen(char *str);
char			*trunc_str_wfree(char *str);
void			stock_supp(const char *str, char *sup, int nb_car, int mode);
char			*ft_strjoin_wfree(char *str, char *buf, int nb_car);
int				newline_in_str(char *str, int nb_car, int mode);

//parser
void			free_pars(t_pars *pars);
void			error_exit(char *error_msg, t_data *d, t_pars *pars,
					char **map);
void			parser(int argc, char **argv, t_pars *pars);

//parse_elements
void			get_path2(t_data *d, t_pars *pars, char *path);
void			get_path(t_data *d, t_pars *pars, t_elems *elems);
void			get_color(t_data *d, t_pars *pars, t_elems *elems);
void			get_elem(t_data *d, t_pars *pars, t_elems *elems);
void			parse_elements(t_data *d, t_pars *pars);

//parse map
char			**copy_map(t_data *d, t_pars *pars, char **map, int nb_lines);
void			parse_map(t_data *d, t_pars *pars);
void			check_valid_map_char(t_data *d, t_pars *pars, int i, int j);
void			is_valid_map(t_data *d, t_pars *pars);

//parser_utils
void			init_values(t_data *d, t_pars *pars);
void			init_elems(t_elems *elems);
char			*get_identifier(t_data *d);
void			get_fd(char *map_arg, char *ext, t_data *d);
int				count_args(char *line);

//parser_utils2
int				is_empty_line(char *line);
void			set_bool_elem(t_data *d, t_elems *elems, t_pars *pars);
void			check_color_format(t_data *d, t_pars *pars);
int				all_elems_found(t_elems elems);
void			get_res(t_data *d, t_pars *pars, t_elems *elems);

//basic functions
int				is_upper(char c);
int				is_digit(char c);
int				is_space(char c);
int				ft_strcmp(char *s1, char *s2);
int				ft_atoi(const char *str);

#endif
