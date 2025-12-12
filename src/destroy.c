/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** destroy.c
*/

#include "../include/my.h"

static void destroy_general(game_t *game)
{
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game->background_texture)
        sfTexture_destroy(game->background_texture);
    if (game->background_sprite)
        sfSprite_destroy(game->background_sprite);
}

void destroy_game(game_t *game)
{
    destroy_general(game);
    free(game);
}
