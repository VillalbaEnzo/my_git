/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** create_matrix.c
*/

#include "my.h"

matrix_t create_matrix(int line, int column)
{
    matrix_t matrix;

    matrix.data = calloc(line * column, sizeof(float));

    if (!matrix.data)
    {
        matrix.line = 0;
        matrix.column = 0;
        return matrix;
    }
    matrix.line = line;
    matrix.column = column;
    return matrix;
}