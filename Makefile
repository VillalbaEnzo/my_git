##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/game/game.c	\
		src/events/manage_events.c	\
		src/create/create_game.c	\
		src/create/create_background.c	\
		src/destroy/destroy_game.c	\
		src/init/init_game.c
OBJ	=	$(SRC:.c=.o)

CC	=	epiclang
CFLAGS = -Wall -Wextra -I include -g3
LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

NAME	=	my_world

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
