/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** push
*/

#include "my.h"

queue_node_t *new_queue_node(room_t *room)
{
    queue_node_t *new = malloc(sizeof(queue_node_t));

    new->room = room;
    new->next = NULL;
    return new;
}

void push(queue_t *queue, room_t *room)
{
    queue_node_t *q_node = new_queue_node(room);

    if (is_empty(queue)) {
        queue->front = q_node;
        queue->back = q_node;
    } else {
        queue->back->next = q_node;
        queue->back = q_node;
    }
}
