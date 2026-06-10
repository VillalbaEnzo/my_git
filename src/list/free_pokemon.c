/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** free_pokemon.c
*/

#include "my.h"

static void free_pokemon(pokemon_t *node)
{
    if (!node)
        return;
    if (node->name)
        free(node->name);
    free(node);
}

void free_pokemons(pokemon_t *head)
{
    pokemon_t *next;

    while (head) {
        next = head->next;
        free_pokemon(head);
        head = next;
    }
}
