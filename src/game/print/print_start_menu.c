/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** print_start_menu.c
*/

#include "my.h"

void start_menu_print(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->start_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->quit_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->load_btn->rect, NULL);
    update_menu_btn(game);
}

void load_print(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->start_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->quit_btn->rect, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->start_menu->load_btn->rect, NULL);
    update_menu_btn(game);
    printf("load mode\n");
}

void playing_print(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    sfRenderWindow_drawText(game->window, game->pl_ui->tb->raise_btn, NULL);
    sfRenderWindow_drawText(game->window, game->pl_ui->tb->lower_btn, NULL);
    sfRenderWindow_drawText(game->window, game->pl_ui->tb->flatten_btn, NULL);
    sfRenderWindow_drawText(game->window, game->pl_ui->tb->smooth_btn, NULL);
    sfRenderWindow_drawText(game->window, game->pl_ui->menu_btn, NULL);
    draw_map(game);
    update_playing_btn(game);
}
