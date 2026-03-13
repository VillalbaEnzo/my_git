/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** construct_path
*/

#include "my.h"

path_t *init_path(void)
{
    path_t *temp = malloc(sizeof(path_t));

    if (!temp)
        return NULL;
    temp->count = 0;
    temp->capacity = 4;
    temp->path = malloc(sizeof(room_t *) * temp->capacity);
    for (int i = 0; i < temp->capacity; i++)
        temp->path[i] = NULL;
    return temp;
}

path_t *construct_path(maze_t *maze)
{
    room_t *current = maze->end;
    path_t *path = init_path();

    if (!path)
        return NULL;
    for (; current != NULL; current = current->parent)
        append(path, current);
    return path;
}
