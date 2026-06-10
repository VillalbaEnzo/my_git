/*
** EPITECH PROJECT, 2025
** utils
** File description:
** fill_array.c
*/

#include "my.h"

void fill_array(array_t *array, char c)
{
    if (!array || !array->array)
        return;
    for (int i = 0; i < array->height; i++) {
        for (int j = 0; j < array->width; j++)
            array->array[i][j] = c;
    }
}
