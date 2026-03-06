/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** bfs
*/

#include "my.h"

void process_neighbors(room_t *curr, queue_t *q)
{
    if (curr->neighbors->room->visited == 0) {
        curr->neighbors->room->visited = 1;
        curr->neighbors->room->parent = curr;
        push(q, curr->neighbors->room);
    }
}

path_t *bfs(maze_t *maze)
{
    queue_t *q = malloc(sizeof(queue_t));
    room_t *curr = NULL;

    q->back = NULL;
    q->front = NULL;
    maze->start->visited = 1;
    maze->start->parent = NULL;
    push(q, maze->start);
    while (!is_empty(q)) {
        curr = pop(q);
        if (curr == maze->end)
            break;
        for (; curr->neighbors != NULL;
            curr->neighbors = curr->neighbors->next)
            process_neighbors(curr, q);
    }
    free(q);
    return construct_path(maze);
}
