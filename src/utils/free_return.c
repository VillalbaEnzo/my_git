/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** free_return
*/

#include "mysh.h"

/**
 * Frees anything you want and returns NULL
 * @param to_free Allocated memory to free
 * @return NULL
 */
void *free_return(void *to_free)
{
    free(to_free);
    return NULL;
}
