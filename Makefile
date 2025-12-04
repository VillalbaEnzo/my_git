##
## EPITECH PROJECT, 2025
## G-PSU-100-LYN-1-1-mysudo-39
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/parser.c	\
		src/auth.c	\
		src/execute.c	\
		src/utils/init.c	\
		src/utils/free_prog.c	\
		src/utils/fill_buf_from_file.c	\
		src/utils/get_user_group_info.c	\
		src/utils/free_struct_s.c	\
		src/utils/file_parser.c	\
		src/utils/strdup.c	\
		src/utils/fill_double_array.c	\
		src/utils/fill_in_group_id.c	\
		src/utils/read_and_cmp_psw_in_stdin.c	\
		src/utils/find.c	\

OBJ	=	$(SRC:.c=.o)

CC = epiclang
CFLAGS += -g3 -Wall -Wextra
LDFLAGS = -lcrypt
NAME =	my_sudo

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	sudo chown root:root my_sudo
	sudo chmod 4755 my_sudo

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re