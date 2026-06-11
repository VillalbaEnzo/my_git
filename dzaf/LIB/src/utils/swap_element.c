/*
** EPITECH PROJECT, 2025
** utils
** File description:
** swap_element.c
*/

#include "my.h"

bool swap_element(array_t *array, coord_t *src, coord_t *dest)
{
    char temp;

    if (!array || !array->array || !src || !dest)
        return false;
    if (src->x < 0 || src->x >= array->width ||
        src->y < 0 || src->y >= array->height)
        return false;
    if (dest->x < 0 || dest->x >= array->width ||
        dest->y < 0 || dest->y >= array->height)
        return false;
    temp = array->array[src->y][src->x];
    array->array[src->y][src->x] = array->array[dest->y][dest->x];
    array->array[dest->y][dest->x] = temp;
    return true;
}
