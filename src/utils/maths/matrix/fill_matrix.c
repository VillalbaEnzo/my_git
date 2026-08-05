/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** fill_matrix.c
*/

#include "my.h"

bool fill_matrix(matrix_t *matrix, int line_idx, int column_idx, float value)
{
    if (matrix->line < line_idx || matrix->column < column_idx)
        return false;
    matrix->data[line_idx * matrix->column + column_idx] = value;
    return true;
}
