
NAME = libft.a

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_itoa_uns.c \
		ft_itoa_pointers.c \
		ft_itoa_hex.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memdup.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putnchar.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_split.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstsplit.c \


HEADER = libft.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror	

RM = rm -rf

AR = ar rc
			

$(NAME):	$(OBJ)
	@echo "Making assignment"
	@$(AR) $(NAME) $(OBJ) $(HEADER)

.c.o:
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	@echo "Making Library"
	@$(AR) $(NAME) $(OBJ)


clean:
	@echo "Removing regular files"
	@$(RM) $(OBJ)

fclean:
	@echo "Removing lib"
	@$(RM) $(NAME) $(OBJ)
	@echo "Removing files *.o  ... \033[32mok\033[0m"


re: fclean all

.PHONY: all clean fclean re
