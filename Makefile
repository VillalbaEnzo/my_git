SRC	=	src/op.c \
		src/main.c \
		src/handler/handle_write.c	\
		src/parsing/parse_header.c \
		src/parsing/parse_commands.c \
		src/parsing/parse_file.c \
		src/error_handling/is_file_valid.c \
		src/utils/my_strncmp.c \
		src/utils/swap_endian.c \
		src/utils/read_line.c \
		src/utils/my_strlen.c \
		src/utils/my_memset.c \
		src/utils/my_calloc.c \
		src/utils/my_strcpy.c \
		src/utils/my_str_to_token_array.c \
		src/utils/my_strcmp.c \
		src/utils/free_array.c \
		src/utils/close_and_return.c \
		src/utils/free_return.c	\
		src/utils/my_strncpy.c	\
		src/utils/my_strcat.c	\
		src/utils/get_final_name.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	robot-factory

CC	=	epiclang

CFLAGS	=	-Iinclude/ -Wall -Wextra

all: $(NAME)

test: CFLAGS += -g3
test: all

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test

