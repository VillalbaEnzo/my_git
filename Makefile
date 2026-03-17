SRC	=	src/core/read_csv.c \
		src/core/write_csv.c \
		src/basic/head.c \
		src/basic/tail.c \
		src/basic/shape.c \
		src/basic/info.c \
		src/basic/describe.c \
		src/others/filtering.c \
		src/sorting/sort.c \
		src/transformation/apply.c \
		src/utilities/get_value.c \
		src/utilities/get_values.c \
		src/utilities/free.c \
		src/my_utils/open_file.c \
		src/my_utils/resizes.c \
		src/my_utils/inits.c \
		src/my_utils/set_type.c \
		src/my_utils/return_value.c \
		src/my_utils/copy.c \
		src/my_utils/find_column.c \

T_SRC	=	tests/main.c

OBJ	=	$(SRC:.c=.o)

T_OBJ	=	$(T_SRC:.c=.o)

NAME	=	libcuddle.a

T_NAME	=	cuddle

CC	=	epiclang

I_PATH	=	include/

CFLAGS	=	-I$(I_PATH) -Wall -Wextra

LDFLAGS	=	-L./

LDLIBS	=	-lm -lcuddle

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

test: CFLAGS += -g3
test: all $(T_NAME)

$(T_NAME): $(T_OBJ)
	$(CC) -o $(T_NAME) $(T_OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(T_OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(T_NAME)
	rm -f $(NAME)

re: fclean all

re_test: fclean test

.PHONY:	all test clean fclean re re_test
