/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** free_maze
*/

#include "my.h"

void free_neighbors(room_t *room)
{
    neighbor_t *temp = NULL;

    while (room->neighbors != NULL) {
        temp = room->neighbors;
        room->neighbors = room->neighbors->next;
        free(temp);
    }
}

void free_maze(maze_t *maze)
{
    room_t *temp = NULL;
    room_t *next = NULL;

    if (!maze)
        return;
    temp = maze->start;
    while (temp) {
        free_neighbors(temp);
        next = temp->next;
        if (temp->name)
            free(temp->name);
        free(temp);
        temp = next;
    }
    free(maze);
}
