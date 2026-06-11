/*
** EPITECH PROJECT, 2025
** utils
** File description:
** move_element.c
*/

#include "my.h"

bool move_element(array_t *array, coord_t *src, coord_t *dest, char basic)
{
    int new_x = 0;
    int new_y = 0;
    char c;

    if (!array || !array->array || !src)
        return false;
    new_x = src->x + dest->x;
    new_y = src->y + dest->y;
    if (new_x < 0 || new_x >= array->width ||
        new_y < 0 || new_y >= array->height)
        return false;
    c = array->array[src->y][src->x];
    array->array[src->y][src->x] = basic;
    array->array[new_y][new_x] = c;
    src->x = new_x;
    src->y = new_y;
    return true;
}
