/*
** EPITECH PROJECT, 2025
** utils
** File description:
** copy_array.c
*/

#include "my.h"

array_t *copy_array(array_t *array)
{
    array_t *new_array = NULL;

    if (!array)
        return NULL;
    new_array = create_array(array->width, array->height);
    if (!new_array)
        return NULL;
    for (int i = 0; i < array->height; i++) {
        for (int j = 0; j < array->width; j++)
            new_array->array[i][j] = array->array[i][j];
    }
    return new_array;
}
