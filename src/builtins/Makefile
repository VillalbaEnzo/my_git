##
## EPITECH PROJECT, 2026
## 42sh
## File description:
## Makefile
##

SRC	=	cd.c \
		env.c \
		exit.c \
		setenv.c \
		unsetenv.c \
		which.c \
		set.c \
		unset.c \
		where.c \
		alias.c \
		unalias.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libbuiltin.a

CC	=	epiclang

CFLAGS	+=	-I$(I_PATH) -Wall -Wextra

I_PATH	=	../../include

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
