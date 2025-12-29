##
## EPITECH PROJECT, 2025
## G-MUL-100-LYN-1-1-myradar-17
## File description:
## Makefile
##

CC	=	epiclang
CC_P	=	gcc

INCLUDES	=	-I./includes \
				-I./lib/my/includes
LDFLAGS		=	-L.
CFLAGS		=	$(INCLUDES) \
				-g3
LIBS		=	-lm

FLAGS		=	$(CFLAGS) $(LDFLAGS) $(LIBS)

NAME		=	my_top

SRC	=	main.c \
		src/my_top.c \
		$(wildcard src/define/*.c) \
		$(wildcard src/free/*.c) \
		$(wildcard src/parsing/*.c) \
		$(wildcard src/utils/*.c)
SRC_LIB	=	$(wildcard lib/my/*.c)

OBJ = $(SRC_LIB:.c=.o)

all:	$(NAME)

$(NAME): lib $(SRC)
	$(CC) $(FLAGS) -o $(NAME) $(SRC) libmy.a

lib: $(OBJ)
	ar rc libmy.a $(OBJ)
	ranlib libmy.a

lib/my/%.o: lib/my/%.c
	$(CC) $(CFLAGS) -c $< -o $@

my: lib
	$(CC_P) $(FLAGS) -o $(NAME) $(SRC) libmy.a

clean:
	$(RM) lib/my/*.o *.o

fclean: clean
	$(RM) $(NAME) libmy.a
	find . -name "*.o" -type f -delete

re: fclean all

auteur:
	echo $(USER) > auteur

.PHONY: all clean fclean re my auteur lib
