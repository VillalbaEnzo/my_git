/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "wolf3d.h"

int print_help(void)
{
    printf("Wolfenstein 3D is a remake of DOOM.\n");
    printf("This is a 3D first-person shooter using a simple");
    printf(" rendering technique called raycasting.\n");
    printf("[USAGE] :\n");
    printf("\tForward: Z\n");
    printf("\tBackward: S\n");
    printf("\tLeft: Q\n");
    printf("\tRight: D\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    game_t *game = NULL;

    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        return print_help();
    game = init_game();
    game_loop(game);
    free_game(game);
    return 0;
}
