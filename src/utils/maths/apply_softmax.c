/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** apply_softmax.c
*/

#include "my.h"

void apply_softmax(matrix_t *matrix)
{
    int matrix_size = matrix->line * matrix->column;
    if (!matrix_size)
        return;
    float max_val = matrix->data[0];

    for (int i = 1; i < matrix_size; i++) {
        if (matrix->data[i] > max_val)
            max_val = matrix->data[i];
    }
    float sum_exp = 0.0;
    for (int i = 0; i < matrix_size; i++) {
        matrix->data[i] = exp(matrix->data[i] - max_val);
        sum_exp += matrix->data[i];
    }
    for (int i = 0; i < matrix_size; i++)
        matrix->data[i] /= sum_exp;
}
