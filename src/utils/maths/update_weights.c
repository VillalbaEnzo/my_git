/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** update_weights.c
*/

#include "my.h"

void update_weights(matrix_t *W, matrix_t dW, float rate)
{
    for (int i = 0; i < W->line * W->column; i++) {
        W->data[i] -= rate * dW.data[i];
    }
}
