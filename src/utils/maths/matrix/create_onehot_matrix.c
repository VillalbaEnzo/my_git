/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** create_onehot_matrix.c
*/

#include "my.h"

matrix_t create_onehot_matrix(int id, int vocab_size)
{
    if (id < 0 || id >= vocab_size) {
        matrix_t error_mat = {0};
        return error_mat;
    }
    matrix_t matrix = create_matrix(vocab_size, 1);
    fill_matrix(&matrix, id, 0, 1.0);
    return matrix;
}
