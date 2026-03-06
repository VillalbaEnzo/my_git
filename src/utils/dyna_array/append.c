/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** append
*/

#include "my.h"

void append(path_t *path, room_t *room)
{
    if (path->count >= path->capacity)
        path = resize(path);
    if (!path)
        return;
    path->path[path->count] = room;
    path->count++;
}
