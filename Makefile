##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	main.c	\
		src/utils/is_num.c	\
        src/utils/open_read.c	\
        src/utils/is_alpha.c	\
        src/utils/my_getnbr.c	\
        src/utils/is_min.c	\
        src/utils/is_maj.c	\
        src/utils/write_file.c	\
        src/handler/handle_min.c	\
        src/handler/handle_maj.c	\
        src/handler/handle_prog.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-I./include

NAME	=	cesar

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
