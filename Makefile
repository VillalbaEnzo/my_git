SRC	=	src/core/read_csv.c \
		src/core/write_csv.c \
		src/basic/head.c \
		src/basic/shape.c \
		src/others/filtering.c \
		src/transformation/apply.c \
		src/utilities/get_value.c \
		src/utilities/free.c \
		src/my_utils/open_file.c \
		src/my_utils/resizes.c \
		src/my_utils/inits.c \
		src/my_utils/set_type.c \

T_SRC	=	tests/main.c

OBJ	=	$(SRC:.c=.o)

T_OBJ	=	$(T_SRC:.c=.o)

NAME	=	libcuddle.a

T_NAME	=	cuddle

CC	=	epiclang

I_PATH	=	include/

CFLAGS	=	-I$(I_PATH) -Wall -Wextra

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

test: CFLAGS += -g3
test: all $(T_NAME)

$(T_NAME): $(T_OBJ)
	$(CC) -o $(T_NAME) $(T_OBJ) -L./ -lcuddle

clean:
	rm -f $(T_OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(T_NAME)
	rm -f $(NAME)

re: fclean all

re_test: fclean test

.PHONY:	all test clean fclean re re_test
