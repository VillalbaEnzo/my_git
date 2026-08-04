/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** compute_gradient_matrix.c
*/

#include "my.h"

matrix_t compute_gradient_matrix(matrix_t dY, matrix_t X, int W_line, int W_column)
{
    matrix_t dW = create_matrix(W_line, W_column);

    for (int i = 0; i < dW.line; i++) {
        for (int j = 0; j < dW.column; j++)
            dW.data[i * W_column + j] = dY.data[i] * X.data[j];
    }
    return dW;
}