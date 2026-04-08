/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** free_return
*/
#include "op.h"

/**
 * Free allocated memory and return NULL (error handling purposes)
 * @param to_free Allocated memory to free
 * @return NULL
 */
void *free_return(void *to_free)
{
    free(to_free);
    return NULL;
}
