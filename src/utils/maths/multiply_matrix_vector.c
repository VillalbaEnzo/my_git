/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** multiply_matrix_vector.c
*/

#include "my.h"

matrix_t multiply_matrix_vector(matrix_t matrix_a, matrix_t matrix_b)
{
    matrix_t result = create_matrix(matrix_a.line, 1);

    for (int i = 0; i < matrix_a.line; i++) {
        for (int j = 0; j < matrix_a.column; j++)
            result.data[i] += matrix_a.data[i * matrix_a.column + j] * matrix_b.data[j];
    }
    return result;
}