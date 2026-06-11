##
## EPITECH PROJECT, 2025
## LIB
## File description:
## Makefile
##

SRC	=	main.c	\
		src/utils/copy_array.c	\
		src/utils/create_array.c	\
		src/utils/fill_array.c	\
		src/utils/free_array.c	\
		src/utils/free_double_array.c	\
		src/utils/get_file.c	\
		src/utils/move_element.c	\
		src/utils/print_array.c	\
		src/utils/set_get_char.c	\
		src/utils/str_to_word_array.c	\
		src/utils/swap_element.c	\

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-I./include

NAME	=	prog

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
