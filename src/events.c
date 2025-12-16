/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** events.c
*/

#include "../include/my.h"

static void close_window(game_t *game, sfEvent event)
{
    if (event.type == sfEvtClosed) {
        sfRenderWindow_close(game->window);
    }
}

static void manage_keyboard(game_t *game, sfEvent event)
{
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyL)
            game->show_hitbox = !game->show_hitbox;
        if (event.key.code == sfKeyS)
            game->show_sprites = !game->show_sprites;
    }
}

void manage_events(game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(game, event);
        manage_keyboard(game, event);
    }
}
