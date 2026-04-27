/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_game.c
*/

#include "structs.h"
#include "wolf3d.h"

void free_game(game_t *game)
{
    if (!game)
        return;
    free_window(game);
    free_ui(game);
    free(game);
}
