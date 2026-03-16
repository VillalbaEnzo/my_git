/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** resize
*/

#include "my.h"

path_t *resize(path_t *old)
{
    path_t *new = malloc(sizeof(path_t));

    if (!new)
        return NULL;
    new->capacity = old->capacity * 2;
    new->count = 0;
    new->path = malloc(sizeof(room_t *) * new->capacity);
    if (!new->path)
        return NULL;
    for (new->count = 0; new->count < old->capacity; new->count++)
        new->path[new->count] = old->path[new->count];
    free(old->path);
    free(old);
    return new;
}
