/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** transpose_matrix.c
*/

#include "my.h"

matrix_t transpose_matrix(matrix_t matrix)
{
    matrix_t transpose_matrix = create_matrix(matrix.column, matrix.line);

    for (int i = 0; i < matrix.column; i++) {
        for (int j = 0; j < matrix.line; j++)
            fill_matrix(&transpose_matrix, i, j, matrix.data[j * matrix.column + i]);
    }
    return transpose_matrix;
}
