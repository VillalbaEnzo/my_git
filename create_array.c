/*
** EPITECH PROJECT, 2025
** utils
** File description:
** char_array_utils.c
*/

#include "my.h"

static bool check_malloc_str(array_t *array, int i)
{
    if (!array->array[i]) {
        for (int j = 0; j < i; j++)
            free(array->array[j]);
        free(array->array);
        free(array);
        return NULL;
    }
    return true;
}

array_t *create_array(int width, int height)
{
    array_t *array = NULL;

    if (width <= 0 || height <= 0)
        return NULL;
    array = malloc(sizeof(array_t));
    if (!array)
        return NULL;
    array->width = width;
    array->height = height;
    array->array = malloc(height * sizeof(char *));
    if (!array->array) {
        free(array);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        array->array[i] = malloc(width * sizeof(char));
        if (!check_malloc_str(array, i))
            return NULL;
    }
    return array;
}
