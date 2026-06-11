/*
** EPITECH PROJECT, 2025
** utils
** File description:
** print_array.c
*/

#include "my.h"

void print_array(array_t *array)
{
    if (!array || !array->array)
        return;
    for (int i = 0; i < array->height; i++) {
        for (int j = 0; j < array->width; j++)
            putchar(array->array[i][j]);
        putchar('\n');
    }
}
