/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "my.h"

int main(int argc, char **argv)
{
    pokemon_t *head = NULL;
    pokemon_t *one = NULL;
    pokemon_t *two = NULL;

    if (argc != 3)
        return 84;
    srand(-1);
    parse_folder("pokecfg", &head);
    head = sort_pokemon(head);
    one = get_node_by_name(head, argv[1]);
    two = get_node_by_name(head, argv[2]);
    if (!one || !two) {
        free_pokemons(head);
        return 84;
    }
    print_pokemon_info(head);
    game_loop(one, two);
    free_pokemons(head);
    return 0;
}
