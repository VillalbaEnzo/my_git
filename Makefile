##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	src/main.c						\
		src/parsing.c					\
		src/list/create_node.c			\
		src/list/init_pokemon.c			\
		src/list/sort_pokemon.c			\
		src/list/free_pokemon.c			\
		src/list/print_pokemon_info.c	\
		src/list/get_node_by_name.c		\
		src/utils/str_to_word_array.c	\
		src/utils/free_double_array.c	\
		src/game/game_loop.c	\

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-I./include

NAME	=	pokemon

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
