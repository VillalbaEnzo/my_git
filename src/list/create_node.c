/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** create_node.c
*/

#include "my.h"

pokemon_t *create_node(pokemon_t *head, char **arg)
{
    pokemon_t *temp = NULL;

    if (!head)
        return init_pokemon(arg);
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = init_pokemon(arg);
    return head;
}
