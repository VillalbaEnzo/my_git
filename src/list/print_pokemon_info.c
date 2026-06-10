/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** print_pokemon_info.c
*/

#include "my.h"

void print_pokemon_info(pokemon_t *head)
{
    pokemon_t *temp = head;

    while (temp) {
        printf("Pokemon %s has %i attack, %i defense, %i speed and %i %s\n",
            temp->name, temp->attack, temp->defense, temp->speed,
            temp->heal, "health");
        temp = temp->next;
    }
}
