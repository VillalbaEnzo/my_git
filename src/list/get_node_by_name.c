/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** get_node_by_name.c
*/

#include "my.h"

pokemon_t *get_node_by_name(pokemon_t *head, char *name)
{
    pokemon_t *curr = head;

    if (!name)
        return NULL;
    while (curr) {
        if (curr->name && strcasecmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}
