# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 16:05:32 by afulmini          #+#    #+#              #
#    Updated: 2021/05/11 17:19:18 by afulmini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS = srcs/elements_parsing.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/hooks.c \
		srcs/map_parsing.c \
		srcs/mlx_utils.c \
		srcs/move_player.c \
		srcs/parsing_basic.c \
		srcs/parsing_utils.c \
		srcs/parsing_utils2.c \
		srcs/parsing.c \
		srcs/raycasting.c \
		srcs/sprites.c \
		srcs/vectors.c \
		srcs/main.c \
		srcs/save_bmp.c

OBJ = $(SRCS:.c=.o)

CCFLAGS = -Wall -Werror -Wextra
RM = rm -rf

MLX = -lmlx -lm -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	gcc $(CCFLAGS) $(OBJ) $(MLX) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) saved_image.bmp

re: fclean all
