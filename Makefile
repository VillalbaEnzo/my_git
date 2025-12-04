##
## EPITECH PROJECT, 2025
## G-CPE-110-LYN-1-1-organized-33
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/add.c	\
		src/del.c	\
		src/disp.c	\
		src/sort.c	\
		src/utils/list_ops.c	\
		src/utils/string_ops.c	\
		src/utils/mini_printf.c	\
		src/utils/my_putchar.c	\
		src/utils/my_putstr.c	\
		src/utils/my_put_nbr.c	\
		src/utils/my_getnbr.c	\
		src/utils/my_strdup.c	\
		src/utils/my_strlen.c	\
		src/utils/my_strcmp.c	\
		src/utils/enume_type_to_name.c	\

OBJ	=	$(SRC:.c=.o)

CC = epiclang
CFLAGS  += -g3 -I./include
# -Wall -Wextra -Werror
LDFLAGS = -L. -lshell
NAME =	organized

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re