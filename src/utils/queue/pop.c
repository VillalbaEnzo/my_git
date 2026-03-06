/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** pop
*/

#include "my.h"

room_t *pop(queue_t *queue)
{
    queue_node_t *temp = NULL;
    room_t *pop_room = NULL;

    if (is_empty(queue))
        return NULL;
    temp = queue->front;
    pop_room = temp->room;
    queue->front = queue->front->next;
    if (!queue->front)
        queue->back = NULL;
    free(temp);
    return pop_room;
}
