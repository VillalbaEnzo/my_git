/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_window.c
*/

#include "wolf3d.h"

void free_window(game_t *game)
{
    if (!game->window)
        return;
    if (game->window->clock)
        sfClock_destroy(game->window->clock);
    if (game->window->render)
        sfRenderWindow_destroy(game->window->render);
    free(game->window);
}
