/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** apply_relu.c
*/

#include "my.h"

void apply_relu(matrix_t matrix)
{
    for (int i = 0; i < matrix.line * matrix.column; i++) {
        if (matrix.data[i] < 0)
            matrix.data[i] = 0;
    }
}
