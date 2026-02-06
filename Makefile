##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	main.c	\
		src/utils/my_strlen.c	\
		src/utils/my_strcmp.c	\
		src/utils/load_input.c	\
		src/utils/my_strncpy.c	\
		src/utils/my_str_to_word_array.c	\
		src/chained_list/add_node.c	\
		src/chained_list/create_node.c	\
		src/chained_list/del_node.c	\
		src/parsing/parsing.c	\
		src/parsing/is_comment.c	\
		src/parsing/is_command.c	\
		src/parsing/is_room.c	\
		src/parsing/is_tunnel.c	\
		src/init/handle_init.c	\
		src/init/init_maze.c	\
		src/init/init_neighbor.c	\
		src/init/init_room.c	\
		src/free/free_double_buf.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

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
