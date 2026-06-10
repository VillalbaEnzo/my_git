/*
** EPITECH PROJECT, 2025
** utils
** File description:
** set_get_char.c
*/

#include "my.h"

char get_char(array_t *array, coord_t *coord)
{
    if (!array || !array->array || !coord || coord->x < 0 ||
        coord->x >= array->width || coord->y < 0 || coord->y >= array->height)
        return '\0';
    return array->array[coord->y][coord->x];
}

bool set_char(array_t *array, coord_t *coord, char c)
{
    if (!array || !array->array || !coord || coord->x < 0 ||
        coord->x >= array->width || coord->y < 0 || coord->y >= array->height)
        return false;
    array->array[coord->y][coord->x] = c;
    return true;
}
