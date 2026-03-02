##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/game/game.c	\
		src/game/print/print_start_menu.c	\
		src/events/manage_events.c	\
		src/create/create_game.c	\
		src/create/create_background.c	\
		src/destroy/destroy_game.c	\
		src/create/start_menu/create_start_btn.c	\
		src/create/start_menu/create_quit_btn.c	\
		src/create/start_menu/create_load_btn.c	\
		src/create/playing/tools_bar/create_raise_btn.c	\
		src/create/playing/tools_bar/create_lower_btn.c	\
		src/create/playing/tools_bar/create_smooth_btn.c	\
		src/create/playing/tools_bar/create_flatten_btn.c	\
		src/create/playing/other/create_menu_btn.c	\
		src/action/start_menu/handle_quit_btn.c	\
		src/action/start_menu/handle_load_btn.c	\
		src/action/start_menu/handle_start_btn.c	\
		src/action/start_menu/update_menu_btn.c	\
		src/action/playing/tools_bar/handle_lower_btn.c	\
		src/action/playing/tools_bar/handle_raise_btn.c	\
		src/action/playing/tools_bar/handle_flatten_btn.c	\
		src/action/playing/tools_bar/handle_smooth_btn.c	\
		src/action/playing/tools_bar/update_tools_bar_btn.c	\
		src/action/playing/other/update_other_btn.c	\
		src/action/playing/other/handle_menu_btn.c	\
		src/action/playing/update_playing_btn.c	\
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
