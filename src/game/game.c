/*
** EPITECH PROJECT, 2025
** GraphicalC
** File description:
** game.c
*/

#include "my.h"

// sfMusic_setLoop(game->music, sfTrue);
// sfMusic_play(game->music);
void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(game->window, sfBlack);
        manage_events(game);
        sfRenderWindow_drawSprite(game->window, game->bg->bg_sp, NULL);
        if (game->state == START_MENU)
            start_menu_print(game);
        if (game->state == PLAYING)
            playing_print(game);
        sfRenderWindow_display(game->window);
        if (game->state == LOADMAP)
            load_print(game);
    }
}
