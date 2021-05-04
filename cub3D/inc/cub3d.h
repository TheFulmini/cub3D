/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:19:59 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/04 14:13:52 by afulmini         ###   ########.fr       */
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

# define BUFFER_SIZE 43

typedef struct s_sprites
{
	double	x;
	double	y;
}				t_sprites;

typedef struct s_sprvar
{
	int		*sprite_order;
	double	*sprite_distance;
	double	*zbuffer;
	double	sprite_y;
	double	sprite_x;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
}				t_sprvar;

typedef struct s_raycast
{
	double	raydirection_x;
	double	raydirection_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	deltadist_y;
	double	deltadist_x;
	double	perpwalldist;
	double	wallx;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		text_num;
	int		text_x;
	int		text_y;
	int		colour;
	double	text_pos;
	double	step;
	double	old_dir_x;
	double	old_plane_x;
	double	move_speed;
	double	turn_speed;
}				t_raycast;

typedef struct s_img
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_parse
{
	int			screen_width;
	int			screen_height;
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
	int			save;
	t_sprites	*sprite_tab;
}				t_parse;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		look_left;
	int		look_right;
	int		text_width[5];
	int		text_height[5];
	t_img	img;
	t_img	img1;
	t_img	text[5];
	t_parse	p;
}				t_mlx;

typedef struct s_elems
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

typedef struct s_data
{
	char	*line;
	char	*id;
	int		fd;
	int		ret;
}				t_data;

/* GNL functions */
unsigned long	ft_strlen(char *str);
char			*truncate_str_free(char *str);
void			stock_supp(const char *str, char *supp, int nb_char, int mode);
char			*ft_strjoin_free(char *str, char *buffer, int nb_char);
int				newline_in_str(char *str, int nb_char, int mode);
int				end_or_error(int ret, char *buffer, char **sup_str, char *line);
int				malloc_str(char **buffer, char **supp, int fd);
char			*ft_strdup(const char *str);
int				make_line(int fd, char *buffer, char **line, char **supp);
int				get_next_line(int fd, char **line);

/* parsing.c */
void			free_parser(t_parse *p);
void			error_exit(char *error_msg, t_data *d, t_parse *p, char **map);
void			check_map(t_data *d, t_parse *p);
void			parsing(int argc, char **argv, t_parse *p);

/* parsing_utils.c */
void			init_values(t_data *d, t_parse *parsing);
void			init_elems(t_elems *e);
char			*get_identifier(t_data *d);
void			get_fd(char *map_arg, char *et, t_data *d);
int				count_arg(char *line);

/* parsing_utils2.c */
int				is_empty(char *line);
void			check_color_format(t_data *d, t_parse *p);
void			set_bool_elem(t_data *d, t_elems *e, t_parse *p);
int				all_elements_found(t_elems e);
void			get_res(t_data *d, t_parse *p, t_elems *e);

/* parsing_basic.c */
int				is_space(char c);
int				is_digit(char c);
int				is_upper(char c);
int				ft_strcmp(char *s1, char *s2);
int				ft_atoi(const char *str);

/* map_parsing.c */
char			**copy_map(t_data *d, t_parse *p, char **map, int nb_lines);
void			map_parsing(t_data *d, t_parse *p);
void			add_sprite_pos(t_parse *p, int i, int j);
void			check_map_char(t_data *d, t_parse *p, int i, int j);
void			check_valid_map(t_data *d, t_parse *p);

/* elements_parsing.c */
void			get_path_bis(t_data *d, t_parse *p, char *path);
void			get_path(t_data *d, t_parse *p, t_elems *e);
void			get_colour(t_data *d, t_parse *p, t_elems *e);
void			get_element(t_data *d, t_parse *p, t_elems *e);
void			parse_elements(t_data *d, t_parse *p);

/* mlx_utils.c */
void			mlx_destroy(t_mlx *d);
void			get_pixel(t_img *img, int x, int y, int *colour);
void			put_pixel(t_img *img, int x, int y, int colour);
void			init_mlx_var(t_mlx *d);

/* hooks.c */
int				key_press(int keycode, t_mlx *d);
int				key_release(int keycode, t_mlx *d);
int				click_exit(t_mlx *d);

/* raycasting.c */
void			set_textures_var(t_mlx *d, t_raycast *r);
void			draw_line(t_mlx *d, t_raycast *r, int x);
void			get_sprite(t_mlx d, t_raycast r, t_sprvar *s);
void			free_sprites_tab(t_sprvar *s);
int				raycasting(t_mlx *d);

/* vectors.c */
void			dda_algorithm(t_raycast *r, t_mlx *d);
void			set_ray_direction_length(t_raycast *r, t_mlx *d);
void			set_raycast_var(t_mlx *d, t_raycast *r, int x);

/* sprites.c */
void			sort_sprites(t_sprvar *sprite, int amount);
int				init_sprite_tab(t_sprvar *s, t_mlx d);
void			set_distance(t_mlx d, t_sprvar *s);
void			set_sprite(t_mlx d, t_sprvar *s);
void			draw_sprite(t_mlx d, t_raycast r, t_sprvar *s);

/* main.c */
int				clean_exit(char *exit_msg, t_parse *p, t_mlx *d, t_sprvar *s);
void			get_vectors_start(t_parse *p);
void			init_moves(t_mlx *d);
void			init_textures(t_mlx *d);
int				main(int argc, char **argv);

/* move_player.c */
void			move_forward_backward(t_mlx *d, t_raycast *r);
void			move_left_rigth(t_mlx *d, t_raycast *r);
void			turn_left_rigth(t_mlx *d, t_raycast *r);
void			get_player_moves(t_mlx *d, t_raycast *r);

/* save_bmp.c */
void	create_header(t_mlx d, int fd);
void	save_bmp(t_mlx d);

#endif
