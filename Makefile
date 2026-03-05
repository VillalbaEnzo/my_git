##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/game/game.c	\
		src/game/display/handle_display.c	\
		src/game/display/display_user_input.c \
		src/game/display/display_brush_ui.c \
		src/events/manage_events.c	\
		src/events/map_events.c	\
		src/create/create_game.c	\
		src/create/create_background.c	\
		src/destroy/destroy_game.c	\
		src/destroy/destroy_map.c	\
		src/create/start_menu/create_start_btn.c	\
		src/create/start_menu/create_quit_btn.c	\
		src/create/start_menu/create_load_btn.c	\
		src/create/playing/tools_bar/create_raise_btn.c	\
		src/create/playing/tools_bar/create_lower_btn.c	\
		src/create/playing/tools_bar/create_smooth_btn.c	\
		src/create/playing/tools_bar/create_flatten_btn.c	\
		src/create/playing/tools_bar/create_brush_ui.c	\
		src/create/playing/other/create_save_btn.c \
		src/create/playing/other/create_menu_btn.c	\
		src/action/start_menu/handle_quit_btn.c	\
		src/action/start_menu/handle_load_btn.c	\
		src/action/start_menu/handle_start_btn.c	\
		src/action/start_menu/update_menu_btn.c	\
		src/action/playing/tools_bar/handle_lower_btn.c	\
		src/action/playing/tools_bar/handle_raise_btn.c	\
		src/action/playing/tools_bar/handle_flatten_btn.c	\
		src/action/playing/tools_bar/handle_smooth_btn.c	\
		src/action/playing/tools_bar/handle_brush_click.c	\
		src/action/playing/tools_bar/update_tools_bar_btn.c	\
		src/action/playing/other/handle_save_btn.c \
		src/action/playing/other/update_other_btn.c	\
		src/action/playing/other/handle_menu_btn.c	\
		src/action/playing/update_playing_btn.c	\
		src/map/isometric.c	\
		src/map/draw_map.c	\
		src/map/handle_map_click.c	\
		src/map/brush/apply_brush.c	\
		src/map/brush/flatten_brush.c	\
		src/map/brush/raise_brush.c	\
		src/map/brush/smooth_brush.c	\
		src/map/brush/lower_brush.c	\
		src/init/init_game.c	\
		src/init/init_map.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang
CFLAGS = -Wall -Wextra -I include -g3
LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

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
