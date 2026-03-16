/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** del_node.c
*/

#include "my.h"

node_t *del_node(node_t *head)
{
    node_t *next;

    if (!head)
        return NULL;
    next = head->next;
    if (next)
        next->end = head->end;
    free(head);
    return next;
}
