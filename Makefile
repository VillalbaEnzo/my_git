SRC	=	src/shell/prompt.c \
		src/shell/read_input.c \
		src/shell/path_handling.c \
		src/shell/sig_handling.c \
		src/shell/redirections/redirections.c \
		src/shell/redirections/redirections_save.c \
		src/shell/execs/exec.c \
		src/shell/execs/flow.c \
		src/shell/execs/pipe.c \
		src/shell/execs/logic_op.c \
		src/shell/globbing/word_exp.c \
		src/shell/errors/error_handling.c \
		src/shell/errors/pipe_error.c \
		src/shell/scripting/add_local_var.c \
		src/shell/scripting/change_var.c \
		src/parsing/builds/build_command.c \
		src/parsing/builds/build_pipe.c \
		src/parsing/builds/build_semi_colon.c \
		src/parsing/builds/build_logic_op.c \
		src/parsing/builds/build_if.c \
		src/parsing/tokenizer.c \
		src/parsing/build_tree.c \
		src/init.c \
		src/frees/free_tree.c \
		src/frees/free_logic_op.c \
		src/frees/free_pipe.c \
		src/frees/free_semi_colon.c \
		src/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

CC	=	epiclang

I_PATH	=	include/

CFLAGS	+=	-I$(I_PATH) -Wall -Wextra

LDFLAGS	=	-Lsrc/utils -Lsrc/builtins

LDLIBS	=	-lbuiltin -lutils

all: $(NAME)

$(NAME): $(OBJ)
	make -C src/utils
	make -C src/builtins
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

debug: CFLAGS += -g3
export CFLAGS
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C src/utils
	make fclean -C src/builtins
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
