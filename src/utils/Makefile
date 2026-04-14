SRC	=	my_putchar.c \
		my_putstrcnt.c \
		my_strcpy.c \
		my_strdup.c \
		my_strlen.c \
		my_strncpy.c \
		count_args.c \
		my_strcmp.c \
		my_strncmp.c \
		my_strcat.c \
		my_put_nbrcnt.c \
		mini_printf.c \
		comparisons.c \
		my_memset.c \
		my_calloc.c


OBJ	=	$(SRC:.c=.o)

NAME	=	libutils.a

CC	=	epiclang

I_PATH	=	../../include

CFLAGS	=	-I$(I_PATH) -Wall -Wextra


all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
