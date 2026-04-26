##
## EPITECH PROJECT, 2025
## G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
## File description:
## Makefile
##

SRC = 	main.c	\
		src/init/init_game.c	\
		src/init/init_window.c	\
		src/init/init_menu.c	\
		src/free/free_game.c	\
		src/core/event/handle_event.c	\
		src/core/event/handle_menu_events.c	\
		src/core/game_loop.c	\
		src/core/display_page.c	\

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang
CFLAGS = -Wall -Wextra -I include -g3
LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

NAME = wolf3d

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re