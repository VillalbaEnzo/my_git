##
## EPITECH PROJECT, 2026
## My Project
## File description:
## Makefile
##

SRC_PATH = src/
UTILS_PATH = utils/
MATRIX_PATH = matrix/
MATHS_PATH = maths/
MODELS_PATH = models/
TRAINNING_PATH = training/

SRC	=	$(SRC_PATH)main.c	\
		$(SRC_PATH)$(UTILS_PATH)backpropagation.c	\
		$(SRC_PATH)$(UTILS_PATH)simple_neurone.c	\
		$(SRC_PATH)$(UTILS_PATH)double_neurone.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATRIX_PATH)create_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATRIX_PATH)print_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATRIX_PATH)fill_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATRIX_PATH)compute_gradient_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)multiply_matrix_vector.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)apply_relu.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)update_weights.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)transpose_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)add_vectors.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)save_model.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)load_model.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)free_model.c	\
		$(SRC_PATH)$(TRAINNING_PATH)train.c	\

OBJ	=	$(SRC:.c=.o)
CC	=	clang
CFLAGS	+=	-I./include
NAME	=	my_llm

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re