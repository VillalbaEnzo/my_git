/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** add_vectors.c
*/

#include "my.h"

void add_vectors(matrix_t *matrix_a, matrix_t matrix_b)
{
    if (matrix_a->line != matrix_b.line || matrix_a->column != matrix_b.column)
        return;
    for (int i = 0; i < matrix_a->line * matrix_a->column; i++)
        matrix_a->data[i] += matrix_b.data[i];
}