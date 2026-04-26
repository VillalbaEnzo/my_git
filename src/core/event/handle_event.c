/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** handle_event.c
*/

#include "structs.h"
#include "wolf3d.h"

void handle_events(game_t *game)
{
    sfEvent event = game->window->event;

    while (sfRenderWindow_pollEvent(game->window->render, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->window->render);
        if (game->state == STATE_MENU)
            handle_menu_events(game, event);
    }
}
