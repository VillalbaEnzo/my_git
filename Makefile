##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	main.c	\
		src/handle_sh.c	\
		src/env/get_env.c	\
		src/utils/my_putstr.c	\
		src/utils/clear_line.c	\
		src/utils/my_strncpy.c	\
		src/utils/my_strlen.c	\
		src/utils/my_putnbr.c	\
		src/utils/my_putchar.c	\
		src/utils/mini_printf.c	\
		src/utils/my_strcmp.c	\
		src/chained_list/add_node.c	\
		src/chained_list/create_node.c	\
		src/chained_list/del_node.c	\
		src/free/free_list.c	\
		src/free/free_double_buf.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-g3 -Wall -I./include

NAME	=	mysh

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
