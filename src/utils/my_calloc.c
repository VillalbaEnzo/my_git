/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** my_calloc
*/

#include "utils.h"
#include <stdlib.h>
#include <stddef.h>

/**
 * Allocate nmemb elements of size bytes each, all set to 0
 * @param nmemb number of elements
 * @param size size of one element
 * @return void pointer to allocated memory, NULL if error
 */
void *my_calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;
    size_t tot_size = nmemb * size;

    if (tot_size == 0)
        return NULL;
    ptr = malloc(tot_size);
    if (!ptr)
        return NULL;
    ptr = my_memset(ptr, 0, tot_size);
    return ptr;
}
