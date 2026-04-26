SRC	=	src/op.c \
		src/main.c \

OBJ	=	$(SRC:.c=.o)

NAME	=	corewar

CC	=	epiclang

CFLAGS	=	-Iinclude/ -Wall -Wextra

all: $(NAME)

vgrind: CFLAGS += -g3
vgrind: all

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re vgrind

