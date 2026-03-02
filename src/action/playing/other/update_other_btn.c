/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** update_tools_bar_btn.c
*/

#include "my.h"

static void update_menu_btn_state(game_t *game, sfVector2f *mouse_pos)
{
    sfText *text = game->pl_ui->menu_btn;
    sfFloatRect bounds = sfText_getGlobalBounds(text);

    if (sfFloatRect_contains(&bounds, mouse_pos->x, mouse_pos->y)) {
        sfText_setFillColor(text, sfColor_fromRGB(255, 165, 0));
        handle_menu_btn(game);
    } else
        sfText_setFillColor(text, sfWhite);
}

void update_other_btn(game_t *game)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(game->window,
        pixel_pos, NULL);

    update_menu_btn_state(game, &mouse_pos);
}
