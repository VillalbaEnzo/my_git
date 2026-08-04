/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** free_matrix.c
*/

#include "my.h"

void print_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.line; i++) {
        for (int j = 0; j < matrix.column; j++)
            printf("%f ", matrix.data[i * matrix.column + j]);
        printf("\n");
    }
}
