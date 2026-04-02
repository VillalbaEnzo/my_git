##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC	=	main.c	\
		utils/my_strlen.c	\
		utils/calculator.c	\
		utils/is_num.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	+=	-g3 -Wall -I./include

NAME	=	gpa_calculator

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
