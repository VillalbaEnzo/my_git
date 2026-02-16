/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** add.c
*/

#include "my.h"

node_t *add_node(node_t *head, char *line)
{
    node_t *new = create_node(line);

    if (!new)
        return head;
    if (!head)
        return new;
    head->end->next = new;
    head->end = new;
    return head;
}
