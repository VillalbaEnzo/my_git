##
## EPITECH PROJECT, 2025
## G-CPE-100-LYN-1-1-cpoolday10-20
## File description:
## Makefile
##

SRC	=	$(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = libmy

all: $(NAME)

$(NAME):	$(SRC) $(OBJ) $(NAME)
	gcc -c $(SRC) -Iincludes
	ar rc $(NAME).a $(OBJ)

clean:
	rm -f lib/my/*.o

fclean:
	rm -f $(NAME)

re: fclean

auteur:
	echo $(USER) > auteur
