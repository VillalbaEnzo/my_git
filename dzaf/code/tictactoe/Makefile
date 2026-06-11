##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC =	main.c \
        src/init_board.c    \
        src/parsing.c   \
        src/free.c  \
        src/my_str_to_word_array.c  \
        src/my_strncpy.c    \
        src/grid.c  \
        src/game_loop.c    \
        src/win_condition.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-I./include

NAME	=	tictactoe

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
