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
    #include <math.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #define Y_TARGET_ONE 0.759
    #define Y_TARGET_TWO 0.1299

float simple_neurone(float x, float w);
float double_neurone(float x[2], float w[2]);
void backpropagation(float x[2], float w[2], float prediction,
    float target_y, float rate);

/* MATRIX */
matrix_t create_matrix(int line, int column);
void print_matrix(matrix_t matrix);
bool fill_matrix(matrix_t *matrix, int line_idx, int column_idx, float value);
matrix_t compute_gradient_matrix(matrix_t dY, matrix_t X, int W_line, int W_column);

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

/* TRAINNING */
bool train(model_t *model, int iteration);

#endif
