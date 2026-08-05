/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

    #include "struct.h"

    #include <stdio.h>
    #include <unistd.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <string.h>
    #include <fcntl.h>

float simple_neurone(float x, float w);
float double_neurone(float x[2], float w[2]);
void backpropagation(float x[2], float w[2], float prediction,
    float target_y, float rate);

/* MATRIX */
matrix_t create_matrix(int line, int column);
void print_matrix(matrix_t matrix);
bool fill_matrix(matrix_t *matrix, int line_idx, int column_idx, float value);
matrix_t compute_weight_gradient(matrix_t dY, matrix_t X,
    int W_line, int W_column);
matrix_t create_onehot_matrix(int id, int vocab_size);
matrix_t compute_output_gradient(matrix_t *Y_pred, matrix_t *Y_target);

/* MATHS */
matrix_t multiply_matrix_vector(matrix_t matrix_a, matrix_t matrix_b);
void apply_relu(matrix_t matrix);
void update_weights(matrix_t *W, matrix_t dW, float rate);
void add_vectors(matrix_t *matrix_a, matrix_t matrix_b);
matrix_t transpose_matrix(matrix_t matrix);

/* MODELS */
bool save_model(model_t model, const char *filename);
bool load_model(model_t *model, const char *filename);
void free_model(model_t *model);
bool save_vocab(vocab_node_t *head, const char *filename);
vocab_node_t *load_vocab(const char *filepath);

/* TRAINNING */
bool train(model_t *model, int iteration);
void tokenizer(const char *filepath, int vocab_target_size);
char *get_pair(text_buffer_t buffer);
void apply_fusion(text_buffer_t *buffer, char *pair);
text_buffer_t init_text_buffer(const char *filepath, bool file);

/* CHAINED LIST */
vocab_node_t *create_node(vocab_node_t *head, int id, const char *token);
void free_list(vocab_node_t *head);
void print_chained_list(vocab_node_t *head);

/* LIB */
char **str_to_word_array(char *str, char *delims);
char *read_file(int fd);
char **get_file(char *filepath);
void free_array(char **str);

#endif
