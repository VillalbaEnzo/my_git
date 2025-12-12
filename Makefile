##
## EPITECH PROJECT, 2025
## G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
## File description:
## Makefile
##

NAME = my_radar
CC = epiclang
CFLAGS = -Wall -Wextra -I include -g3
LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

SRC =	src/create.c	\
		src/destroy.c	\
		src/events.c	\
		src/game.c	\
		src/main.c	\
		src/init.c	\
		src/utils/mini_printf.c	\
		src/utils/my_put_nbr.c	\
		src/utils/my_putchar.c	\
		src/utils/my_putstr.c	\
		src/utils/my_strcmp.c	\
		src/utils/my_revstr.c	\
		src/utils/unsigned_int_to_str.c	\
		src/utils/my_strlen.c	\
		src/utils/my_strcpy.c	\
		src/utils/my_getnbr.c	\
		src/utils/my_str_to_word_array.c	\
		src/utils/free_array.c	\
		config/get_plane_config.c	\
		src/objets/background.c	\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
