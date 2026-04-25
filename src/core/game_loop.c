/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** game_loop.c
*/

#include "structs.h"
#include "wolf3d.h"

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window->render)) {
        game->window->dt =
            sfTime_asSeconds(sfClock_restart(game->window->clock));
        handle_events(game);
        sfRenderWindow_clear(game->window->render, sfBlack);
        sfRenderWindow_display(game->window->render);
    }
}
