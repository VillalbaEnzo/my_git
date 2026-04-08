/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** free_array
*/

#include <stdlib.h>

/**
 * Frees any type of arrays
 * @param array an array of any type (casted to void ** if not void **)
 */
void free_array(void **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
