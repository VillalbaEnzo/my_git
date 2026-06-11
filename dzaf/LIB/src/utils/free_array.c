/*
** EPITECH PROJECT, 2025
** utils
** File description:
** free_array.c
*/

#include "my.h"

void free_array(array_t *array)
{
    if (!array)
        return;
    for (int i = 0; i < array->height; i++)
        if (array->array[i])
            free(array->array[i]);
    if (array->array)
        free(array->array);
    free(array);
}
