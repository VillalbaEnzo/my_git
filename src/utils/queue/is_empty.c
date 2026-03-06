/*
** EPITECH PROJECT, 2026
** amazed [WSL: Ubuntu]
** File description:
** is_empty
*/

#include "my.h"

int is_empty(queue_t *queue)
{
    return (queue->front == NULL);
}
