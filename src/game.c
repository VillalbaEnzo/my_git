/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** game.c
*/

#include "../include/my.h"

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        manage_events(game);
        sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
        sfRenderWindow_display(game->window);
    }
}
