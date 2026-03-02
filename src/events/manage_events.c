/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** manage_events.c
*/

#include "my.h"

static void close_window(game_t *game, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(game->window);
}

static void get_mouse_clicked(game_t *game, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        game->mouse_clicked = true;
    }
}

void manage_events(game_t *game)
{
    sfEvent event;

    game->mouse_clicked = false;
    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(game, event);
        get_mouse_clicked(game, event);
        handle_map_events(game, event);
    }
}
