##
## EPITECH PROJECT, 2025
## G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
## File description:
## Makefile
##

NAME	=	libmy.a

CC	=	epiclang
CFLAGS	=	-I./include
AR	=	ar rc
RM	=	rm -f

SRC	=	my_printf.c		\
		parser.c		\
		handlers/char.c		\
		handlers/conversion.c	\
		handlers/int.c		\
		handlers/str.c		\
		handlers/unsigned.c	\
		handlers/float.c	\
		handlers/scientific.c	\
		handlers/float_auto.c	\
		handlers/octal.c	\
		handlers/hexa.c		\
		handlers/pointer.c		\
		handlers/n_specifier.c	\
		handlers/hexa_float.c	\
		utils/my_getnbr.c	\
		utils/my_putchar.c	\
		utils/my_put_nbr.c	\
		utils/my_put_nbr_octal.c \
		utils/my_put_hexa.c	\
		utils/my_put_float.c	\
		utils/my_power.c	\
		utils/my_putnstr.c	\
		utils/my_putnwstr.c	\
		utils/my_putstr.c	\
		utils/my_putwchar.c	\
		utils/my_strlen.c	\
		utils/my_wstrlen.c	\
		utils/wchar.c		\
		utils/wchar_n_bytes.c	\
		utils/print_padding.c	\
		utils/float_special.c	\
		utils/get_sign.c	\
		utils/print_number.c	\
		utils/count_digits.c

OBJ	=	$(SRC:.c=.o)

TEST_SRC =	tests/test_format_percent.c	\
		tests/test_format_c.c		\
		tests/test_format_s.c		\
		tests/test_format_di.c		\
		tests/test_format_u.c		\
		tests/test_format_o.c		\
		tests/test_format_xX.c		\
		tests/test_format_p.c		\
		tests/test_format_misc.c	\
		tests/test_format_n.c		\
		tests/test_format_aA.c		\
		tests/test_format_f.c		\
		tests/test_hard_format_s.c	\
		tests/test_hard_format_i.c	\
		tests/test_hard_format_dynamic.c	\
		tests/test_hard_format_combi.c	\
		tests/test_hard_format_f.c				\

TEST_BIN =	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_BIN)
	$(RM) *.gcda *.gcno

re: fclean all

unit_tests: fclean $(NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) -L. -lmy -lcriterion --coverage

tests_run: unit_tests
	./$(TEST_BIN)
	$(RM) *.gcda *.gcno

.PHONY: all clean fclean re unit_tests tests_run