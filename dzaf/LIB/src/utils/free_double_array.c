/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** free_double_array.c
*/

#include "my.h"

void free_double_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++) {
        if (array[i])
            free(array[i]);
    }
    free(array);
}
