##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	main.c	\
		src/utils/my_strlen.c	\
		src/utils/my_strcmp.c	\
		src/utils/my_getnbr.c	\
		src/utils/is_nbr.c	\
		src/utils/load_input.c	\
		src/utils/mini_printf.c	\
		src/utils/my_putchar.c	\
		src/utils/my_putstr.c	\
		src/utils/my_put_nbr.c	\
		src/utils/my_strncpy.c	\
		src/utils/my_str_to_word_array.c	\
		src/chained_list/add_node.c	\
		src/chained_list/create_node.c	\
		src/chained_list/del_node.c	\
		src/parsing/parsing.c	\
		src/parsing/is_command.c	\
		src/parsing/is_room.c	\
		src/parsing/is_tunnel.c	\
		src/init/init_maze.c	\
		src/init/init_neighbor.c	\
		src/init/init_room.c	\
		src/free/free_double_buf.c	\
		src/handle/handle_print.c	\
		src/handle/handle_init.c	\
		src/utils/my_strdup.c \
		src/maze/add_room.c \
		src/maze/add_tunnel.c

OBJ	=	$(SRC:.c=.o)

CC	=	clang

CFLAGS	+=	-g3 -Wall -I./include

NAME	=	amazed

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
