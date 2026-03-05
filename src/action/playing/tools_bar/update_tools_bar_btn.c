/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** update_tools_bar_btn.c
*/

#include "my.h"

static void update_lower_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    sfText *text = game->pl_ui->tb->lower_btn;
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    if (game->pl_ui->ui_state == LOWER)
        sfText_setFillColor(text, sfGreen);
    else if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfText_setFillColor(text, sfColor_fromRGB(255, 165, 0));
        handle_lower_btn(game);
    } else
        sfText_setFillColor(text, sfWhite);
}

static void update_raise_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    sfText *text = game->pl_ui->tb->raise_btn;
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    if (game->pl_ui->ui_state == RAISE)
        sfText_setFillColor(text, sfGreen);
    else if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfText_setFillColor(text, sfColor_fromRGB(255, 165, 0));
        handle_raise_btn(game);
    } else
        sfText_setFillColor(text, sfWhite);
}

static void update_flatten_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    sfText *text = game->pl_ui->tb->flatten_btn;
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    if (game->pl_ui->ui_state == FLATTEN)
        sfText_setFillColor(text, sfGreen);
    else if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfText_setFillColor(text, sfColor_fromRGB(255, 165, 0));
        handle_flatten_btn(game);
    } else
        sfText_setFillColor(text, sfWhite);
}

static void update_smooth_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    sfText *text = game->pl_ui->tb->smooth_btn;
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    if (game->pl_ui->ui_state == SMOOTH)
        sfText_setFillColor(text, sfGreen);
    else if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfText_setFillColor(text, sfColor_fromRGB(255, 165, 0));
        handle_smooth_btn(game);
    } else
        sfText_setFillColor(text, sfWhite);
}

void update_tools_bar_btn(game_t *game)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game->window,
        pixel_pos, NULL);

    update_lower_btn_state(game, &mouse_pos);
    update_raise_btn_state(game, &mouse_pos);
    update_smooth_btn_state(game, &mouse_pos);
    update_flatten_btn_state(game, &mouse_pos);
}
