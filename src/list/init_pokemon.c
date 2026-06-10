/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** init_pokemon.c
*/

#include "my.h"

pokemon_t *init_pokemon(char **arg)
{
    pokemon_t *pokemon = malloc(sizeof(pokemon_t));

    if (!pokemon)
        return NULL;
    pokemon->name = strdup(arg[0]);
    pokemon->attack = atoi(arg[1]);
    pokemon->defense = atoi(arg[2]);
    pokemon->speed = atoi(arg[3]);
    pokemon->heal = atoi(arg[4]);
    pokemon->next = NULL;
    return pokemon;
}
