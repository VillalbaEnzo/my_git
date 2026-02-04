/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** create_node.c
*/

#include "my.h"

node_t *create_node(char *line)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;
    node->line = my_strdup(line);
    if (!node->line) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}
