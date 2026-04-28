##
## EPITECH PROJECT, 2025
## G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
## File description:
## Makefile
##

NAME = wolf3d

CC	=	epiclang

ROOT_D			=	./
INCLUDE			=	include/
SRC_D			=	src/
OBJ_D			=	obj/

CORE_D			=	$(SRC_D)core/
EVENT_D			=	$(CORE_D)event/
INIT_D			=	$(SRC_D)init/
FREE_D			=	$(SRC_D)free/
RENDER_D		=	$(SRC_D)render/

CPPFLAGS		=	-I$(INCLUDE)
CFLAGS 			= 	-Wall -Wextra
CFLAGS_DEBUG	=	-g3

LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

SRC				=	$(INIT_D)init_game.c				\
					$(INIT_D)init_window.c				\
					$(INIT_D)init_audio.c				\
					$(INIT_D)init_setting.c				\
					$(INIT_D)init_menu.c				\
					$(INIT_D)init_ui.c					\
					$(INIT_D)init_levels.c				\
					$(INIT_D)init_player.c				\
					$(FREE_D)free_game.c				\
					$(FREE_D)free_window.c				\
					$(FREE_D)free_audio.c				\
					$(FREE_D)free_ui.c					\
					$(FREE_D)free_levels.c				\
					$(CORE_D)game_loop.c				\
					$(CORE_D)display_page.c				\
					$(EVENT_D)handle_event.c			\
					$(EVENT_D)handle_menu_events.c		\
					$(EVENT_D)handle_settings_events.c	\
					$(EVENT_D)handle_movement.c	\
					$(RENDER_D)render.c
OBJ				=	$(SRC:%.c=$(OBJ_D)%.o)


MAIN			=	main.c
MAIN_OBJ		=	$(MAIN:%.c=$(OBJ_D)%.o)


all:	$(NAME)

$(NAME):	$(OBJ)	$(MAIN_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_D)%.o:	%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CPPFLAGS) $(CFLAGS)

debug:	CFLAGS += $(CFLAGS_DEBUG)
debug:	all

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug	clean fclean re
