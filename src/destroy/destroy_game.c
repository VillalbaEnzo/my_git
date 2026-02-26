/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** destroy_game.c
*/

#include "my.h"

void destroy_bg(game_t *game)
{
    if (game->bg->bg_sp)
        sfSprite_destroy(game->bg->bg_sp);
    if (game->bg->bg_tx)
        sfTexture_destroy(game->bg->bg_tx);
    free(game->bg);
}

void destroy_game(game_t *game)
{
    destroy_bg(game);
}
