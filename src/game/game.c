/*
** EPITECH PROJECT, 2025
** GraphicalC
** File description:
** game.c
*/

#include "my.h"

// sfMusic_setLoop(game->music, sfTrue);
// sfMusic_play(game->music);

void start_menu_print(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->start_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->quit_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->load_btn->rect, NULL);
    sfRenderWindow_display(game->window);
    update_menu_btn(game);
}
// void load_print(game_t *game)
// {
//     sfRenderWindow_drawRectangleShape(game->window,
//         game->start_menu->start_btn->rect, NULL);
//     sfRenderWindow_drawRectangleShape(game->window,
//         game->start_menu->quit_btn->rect, NULL);
//     sfRenderWindow_drawRectangleShape(game->window,
//         game->start_menu->load_btn->rect, NULL);
//     sfRenderWindow_display(game->window);
//     update_menu_btn(game);
// }

void playing_print(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    printf("playing mode\n");
}

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
        // if (game->state == LOADMAP)
        //     load_print(game);
        printf("test\n");
    }
}
