/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** sort_pokemon.c
*/

#include "my.h"

pokemon_t *sort_pokemon(pokemon_t *head)
{
    pokemon_t *ret = NULL;
    pokemon_t *curr = NULL;
    pokemon_t *next = NULL;
    pokemon_t **pos = NULL;

    curr = head;
    while (curr) {
        next = curr->next;
        pos = &ret;
        while (*pos && strcasecmp((*pos)->name, curr->name) < 0)
            pos = &(*pos)->next;
        curr->next = *pos;
        *pos = curr;
        curr = next;
    }
    return ret;
}
