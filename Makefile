SRC	=	src/op.c \
		src/main.c \
		src/handler/handle_write.c	\
		src/parsing/parse_header.c \
		src/parsing/parse_commands.c \
		src/parsing/parse_file.c \
		src/parsing/parse_body.c \
		src/parsing/parse_instruction.c \
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
		src/utils/clean_line.c	\
		src/utils/my_getnbr.c	\

TEST_SRC	=	tests/utils_test.c

OBJ	=	$(SRC:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.o)

TEST_BIN	=	unit_tests

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
	rm -f $(TEST_OBJ)
	rm -f *gcda
	rm -f *gcno
	rm -f $(TEST_BIN)

re: fclean all

TEMP_SRC := $(SRC)
TO_AVOID	:=	src/main.c
TEMP_SRC	= $(filter-out $(TO_AVOID), $(SRC))
tests_run: all $(TEST_OBJ)
	gcc -o $(TEST_BIN) $(TEMP_SRC) $(TEST_OBJ) -Iinclude --coverage -lcriterion
	./$(TEST_BIN)

.PHONY: all clean fclean re test tests_run

