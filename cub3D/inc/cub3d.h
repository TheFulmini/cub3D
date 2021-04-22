/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:19:59 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 17:14:45 by afulmini         ###   ########.fr       */
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



#endif