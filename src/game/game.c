/*
** EPITECH PROJECT, 2025
** GraphicalC
** File description:
** game.c
*/

#include "my.h"

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(game->window, sfBlack);
        manage_events(game);
        sfRenderWindow_drawSprite(game->window, game->bg->bg_sp, NULL);
        if (game->state == START_MENU)
            start_menu_display(game);
        if (game->state == PLAYING) {
            handle_map_click(game);
            playing_display(game);
        }
        if (game->state == LOADMAP)
            load_display(game);
        sfRenderWindow_display(game->window);
    }
}
