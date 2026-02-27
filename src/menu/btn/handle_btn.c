/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_menu.c
*/

#include "my.h"

static void handle_hover_start_btn(game_t *game, sfVector2i *pos)
{
    button_t *start_btn = game->start_menu->start_btn;

    if (pos->x >= 810 && pos->x <= 1110 && pos->y >= 385 && pos->y <= 455) {
        sfRectangleShape_setOutlineThickness(start_btn->rect, 10.0);
        handle_start_btn(game);
    } else
        sfRectangleShape_setOutlineThickness(start_btn->rect, 0.0);
}

static void handle_hover_load_btn(game_t *game, sfVector2i *pos)
{
    button_t *load_btn = game->start_menu->load_btn;

    if (pos->x >= 810 && pos->x <= 1110 && pos->y >= 505 && pos->y <= 575) {
        sfRectangleShape_setOutlineThickness(load_btn->rect,
            10.0);
        handle_load_btn(game);
    } else
        sfRectangleShape_setOutlineThickness(load_btn->rect,
            0.0);
}

static void handle_hover_quit_btn(game_t *game, sfVector2i *pos)
{
    button_t *quit_btn = game->start_menu->quit_btn;

    if (pos->x >= 810 && pos->x <= 1110 && pos->y >= 625 && pos->y <= 695) {
        sfRectangleShape_setOutlineThickness(quit_btn->rect,
            10.0);
        handle_quit_btn(game);
    } else
        sfRectangleShape_setOutlineThickness(quit_btn->rect,
            0.0);
}

void handle_hover_btn(game_t *game)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(game->window);

    handle_hover_start_btn(game, &pos);
    handle_hover_load_btn(game, &pos);
    handle_hover_quit_btn(game, &pos);
}
