/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "my.h"

static void print_help(void)
{
    printf("a faire");
    return;
}

int main(int argc, char **argv)
{
    game_t *game;

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }
    if (argc == 1) {
        game = create_game();
        if (!game)
            return 84;
        game_loop(game);
        destroy_game(game);
        return 0;
    }
    return 84;
}
