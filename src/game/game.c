/*
** EPITECH PROJECT, 2025
** GraphicalC
** File description:
** game.c
*/

#include "my.h"

void game_loop(game_t *game)
{
    // sfMusic_setLoop(game->music, sfTrue);
    // sfMusic_play(game->music);
    while (sfRenderWindow_isOpen(game->window)) {
        manage_events(game);
        sfRenderWindow_clear(game->window, sfBlack);
        sfRenderWindow_drawSprite(game->window, game->bg->bg_sp, NULL);
        sfRenderWindow_drawRectangleShape(game->window,
            game->start_menu->start_btn->rect, NULL);
        sfRenderWindow_display(game->window);
    }
}
