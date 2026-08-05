/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** compute_output_gradient.c
*/

#include "my.h"

matrix_t compute_output_gradient(matrix_t *Y_pred, matrix_t *Y_target)
{
    matrix_t dz = create_matrix(Y_pred->line, Y_pred->column);

    for (int i = 0; i < dz.line * dz.column; i++)
        dz.data[i] = Y_pred->data[i] - Y_target->data[i];
    return dz;
}
