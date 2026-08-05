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
CHAINED_LIST_PATH = chained_list/
TRAINING_PATH = training/
VOCAB_PATH = vocab/
LIB_PATH = lib/
TOKENS_PATH = tokens/

SRC	=	$(SRC_PATH)main.c	\
		$(SRC_PATH)$(UTILS_PATH)backpropagation.c	\
		$(SRC_PATH)$(UTILS_PATH)simple_neurone.c	\
		$(SRC_PATH)$(UTILS_PATH)double_neurone.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)create_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)print_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)fill_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)compute_weight_gradient.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)compute_output_gradient.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)$(MATRIX_PATH)create_onehot_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)multiply_matrix_vector.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)apply_relu.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)update_weights.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)transpose_matrix.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MATHS_PATH)add_vectors.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)save_model.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)load_model.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)free_model.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)$(VOCAB_PATH)save_vocab.c	\
		$(SRC_PATH)$(UTILS_PATH)$(MODELS_PATH)$(VOCAB_PATH)load_vocab.c	\
		$(SRC_PATH)$(UTILS_PATH)$(CHAINED_LIST_PATH)create_node.c	\
		$(SRC_PATH)$(UTILS_PATH)$(CHAINED_LIST_PATH)free_list.c	\
		$(SRC_PATH)$(UTILS_PATH)$(CHAINED_LIST_PATH)print_chained_list.c	\
		$(SRC_PATH)$(UTILS_PATH)$(LIB_PATH)str_to_word_array.c	\
		$(SRC_PATH)$(UTILS_PATH)$(LIB_PATH)get_file.c	\
		$(SRC_PATH)$(UTILS_PATH)$(LIB_PATH)read_file.c	\
		$(SRC_PATH)$(UTILS_PATH)$(LIB_PATH)free_array.c	\
		$(SRC_PATH)$(TRAINING_PATH)train.c	\
		$(SRC_PATH)$(TOKENS_PATH)tokenizer.c	\
		$(SRC_PATH)$(TOKENS_PATH)get_pair.c	\
		$(SRC_PATH)$(TOKENS_PATH)apply_fusion.c	\
		$(SRC_PATH)$(TOKENS_PATH)init_text_buffer.c	\
		$(SRC_PATH)$(TOKENS_PATH)encode_text.c	\

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