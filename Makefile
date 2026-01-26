##
## EPITECH PROJECT, 2025
## Secured
## File description:
## Makefile
##

SRC_TEST	=	test/main.c	\

OBJ_TEST	=	$(SRC_TEST:.c=.o)

SRC	=	src/delete_hashtable.c \
		src/hash.c \
		src/ht_insert.c \
		src/ht_delete.c \
		src/ht_dump.c \
		src/ht_search.c \
		src/new_hashtable.c \
		src/utils/mini_printf.c	\
		src/utils/my_bubble_sort.c	\
		src/utils/my_compute_power_rec.c	\
		src/utils/my_compute_square_root.c	\
		src/utils/my_find_prime_sup.c	\
		src/utils/my_getnbr.c	\
		src/utils/my_isneg.c	\
		src/utils/my_is_prime.c	\
		src/utils/my_putchar.c	\
		src/utils/my_put_nbr.c	\
		src/utils/my_putstr.c	\
		src/utils/my_revstr.c	\
		src/utils/my_showmem.c	\
		src/utils/my_show_word_array.c	\
		src/utils/my_sort_int_array.c	\
		src/utils/my_strcapitalize.c	\
		src/utils/my_strcat.c	\
		src/utils/my_strcmp.c	\
		src/utils/my_strcpy.c	\
		src/utils/my_strdup.c	\
		src/utils/my_str_isalpha.c	\
		src/utils/my_str_islower.c	\
		src/utils/my_str_isnum.c	\
		src/utils/my_str_isprintable.c	\
		src/utils/my_str_isupper.c	\
		src/utils/my_strlen.c	\
		src/utils/my_strlowcase.c	\
		src/utils/my_strncat.c	\
		src/utils/my_strncmp.c	\
		src/utils/my_strncpy.c	\
		src/utils/my_strstr.c	\
		src/utils/my_str_to_word_array.c	\
		src/utils/my_strupcase.c	\
		src/utils/my_swap.c	\

TEST_SRC =	tests/test_utils.c	\

OBJ	=	$(SRC:.c=.o)

I_PATH	=	./include

CC	=	epiclang

CFLAGS	=	-g3 -Wall -Wextra -I$(I_PATH)

B_NAME	=	secured

NAME	=	libhashtable.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

test: all $(B_NAME)

$(B_NAME): $(OBJ_TEST)
	$(CC) -o $(B_NAME) $(OBJ_TEST) -L. -lhashtable

clean:
	rm -f test/main.o
	rm -f $(OBJ)

fclean: clean
	rm -f $(B_NAME)
	rm -f $(NAME)

re: fclean all

re_test: fclean test

unit_tests: fclean $(NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(B_NAME) -L. -lmy -lcriterion --coverage

tests_run: unit_tests
	./$(TEST_BIN)
	$(RM) *.gcda *.gcno

.PHONY: test clean fclean re all re_test unit_tests tests_run