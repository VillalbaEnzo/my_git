/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** update_menu_buttons.c
*/

#include "my.h"

static void update_start_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    button_t *start_btn = game->start_menu->start_btn;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(start_btn->rect);

    if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfRectangleShape_setOutlineThickness(start_btn->rect, 10.0);
        handle_start_btn(game);
    } else {
        sfRectangleShape_setOutlineThickness(start_btn->rect, 0.0);
    }
}

static void update_load_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    button_t *load_btn = game->start_menu->load_btn;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(load_btn->rect);

    if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfRectangleShape_setOutlineThickness(load_btn->rect, 10.0);
        handle_load_btn(game);
    } else {
        sfRectangleShape_setOutlineThickness(load_btn->rect, 0.0);
    }
}

static void update_quit_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    button_t *quit_btn = game->start_menu->quit_btn;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(quit_btn->rect);

    if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfRectangleShape_setOutlineThickness(quit_btn->rect, 10.0);
        handle_quit_btn(game);
    } else {
        sfRectangleShape_setOutlineThickness(quit_btn->rect, 0.0);
    }
}

void update_menu_btn(game_t *game)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game->window,
        pixel_pos, NULL);

    update_start_btn_state(game, &mouse_pos);
    update_load_btn_state(game, &mouse_pos);
    update_quit_btn_state(game, &mouse_pos);
}
