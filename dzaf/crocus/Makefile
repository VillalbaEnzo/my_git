##
## EPITECH PROJECT, 2025
## crocus
## File description:
## Makefile
##

NAME = crocus

CC = epiclang

SRC = 	src/main.c                      \
        src/handle_error.c              \
        src/handle_number/print_nbr.c   \
        src/handle_number/number.c      \
        src/free_ret.c                  \
        src/parsing/handle_parsing.c    \
        src/parsing/init_parsing.c    \
        src/create_string.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Iinclude

all:	$(NAME)

debug:	CFLAGS += -g3
debug:	all
debugre: debug re

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re debug debug re
