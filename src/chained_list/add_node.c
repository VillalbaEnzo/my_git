/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** add.c
*/

#include "my.h"

node_t *add_node(node_t *head, char *line)
{
    node_t *current = NULL;
    node_t *new = create_node(line);

    if (!new)
        return head;
    if (!head)
        return new;
    current = head;
    while (current->next)
        current = current->next;
    current->next = new;
    return head;
}
