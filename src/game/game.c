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
        manage_events(game);
        sfRenderWindow_clear(game->window, sfBlack);
        sfRenderWindow_drawSprite(game->window, game->bg->bg_sp, NULL);
        sfRenderWindow_drawRectangleShape(game->window,
            game->start_menu->start_btn->rect, NULL);
        sfRenderWindow_drawRectangleShape(game->window,
            game->start_menu->quit_btn->rect, NULL);
        sfRenderWindow_drawRectangleShape(game->window,
            game->start_menu->load_btn->rect, NULL);
        sfRenderWindow_display(game->window);
        handle_hover_btn(game);
    }
}
